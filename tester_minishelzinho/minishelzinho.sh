#!/usr/bin/env bash
MINISHELL_PATH="../minishell"
EXPECT_RUNNER="./expect_runner.exp"
TESTS_FILE="./tests.csv"

PASS=0
FAIL=0
TOTAL=0
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
CYAN=$(tput setaf 6)
RESET=$(tput sgr0)

BRIEF_RESULTS=()
FAIL_DETAILS=()

print_in_columns() {
    local arr=("$@")
    local arr_len=${#arr[@]}
    local cols=3
    local rows=$(( (arr_len + cols - 1) / cols ))
    for ((r = 0; r < rows; r++)); do
        local line_output=""
        for ((c = 0; c < cols; c++)); do
            local idx=$(( c * rows + r ))
            if (( idx < arr_len )); then
                line_output+="$(printf "%-70s" "${arr[idx]}")"
            else
                line_output+="$(printf "%-70s" "")"
            fi
        done
        echo -e "$line_output"
    done
}

strip_ansi() {
    sed -r 's/\x1B\[[0-9;]*[mK]//g'
}

pad_right_noansi() {
    local text="$1"
    local width="$2"
    local vis_len
    vis_len=$(echo -n "$text" | strip_ansi | wc -c | tr -d ' ')
    if (( vis_len >= width )); then
        echo -n "$(echo -n "$text" | sed -E "s/^(.{1,$width}).*/\\1/")"
    else
        local pad=$((width - vis_len))
        printf "%s%*s" "$text" "$pad" ""
    fi
}

center_text_noansi() {
    local text="$1"
    local width="$2"
    local len=${#text}
    if (( len >= width )); then
        echo "${text:0:width}"
        return
    fi
    local left=$(((width - len) / 2))
    local right=$((width - len - left))
    printf "%*s%s%*s" "$left" "" "$text" "$right" ""
}

print_detailed_failures_single() {
    local arr=("$@")
    local term_w=$(tput cols 2>/dev/null || echo 80)
    if ! [[ "$term_w" =~ ^[0-9]+$ ]]; then term_w=80; fi
    (( term_w < 60 )) && term_w=60
    (( term_w > 140 )) && term_w=140
    local inner_w=$((term_w - 4))
    for block in "${arr[@]}"; do
        IFS=$'\n' read -rd '' -a lines <<< "$(echo -e "$block")" || true
        [ ${#lines[@]} -eq 0 ] && lines=( "" )
        local raw_first="$(echo "${lines[0]}" | strip_ansi)"
        local id_token="$(echo "$raw_first" | awk '{print $1}' 2>/dev/null || echo "")"
        [ -z "$id_token" ] && id_token="$raw_first"
        local header_plain="${id_token} FAIL"
        local header_centered
        header_centered=$(center_text_noansi "$header_plain" "$inner_w")
        header_centered="$(echo "$header_centered" | sed "s/ FAIL/ ${RED}FAIL${RESET}/")"
        printf "%s\n" "$(printf '%*s' "$term_w" '' | tr ' ' '-')"
        printf "| %s |\n" "$header_centered"
        printf "| %s |\n" "$(pad_right_noansi "" "$inner_w")"
        for ((i = 1; i < ${#lines[@]}; i++)); do
            local content="${lines[i]}"
            content="$(echo -n "$content" | sed -E 's/^[ \t]+|[ \t]+$//g')"
            if [ -z "$content" ]; then
                printf "| %s |\n" "$(pad_right_noansi "" "$inner_w")"
            else
                local rem="$content"
                while [ -n "$rem" ]; do
                    local take="$(echo -n "$rem" | sed -E "s/^(.{1,$inner_w}).*/\\1/")"
                    printf "| %s |\n" "$(pad_right_noansi "$take" "$inner_w")"
                    rem="${rem#"$take"}"
                    rem="$(echo -n "$rem" | sed -E 's/^[ \t]+//')"
                done
            fi
        done
        printf "%s\n\n" "$(printf '%*s' "$term_w" '' | tr ' ' '-')"
    done
}

show_progress_bar() {
    local current=$1
    local total=$2
    local width=50
    if (( total == 0 )); then
        printf "\r${YELLOW}🔄 Progresso:${RESET} [%-${width}s] %3s%%" "" "0"
        return
    fi
    local percent=$(( current * 100 / total ))
    local filled=$(( current * width / total ))
    local empty=$(( width - filled ))
    local bar=""
    for ((i = 0; i < filled; i++)); do bar+="█"; done
    for ((i = 0; i < empty; i++)); do bar+=" "; done
    printf "\r${YELLOW}🔄 Progresso:${RESET} [${bar}] ${percent}%%"
}

run_test() {
    local id="$1" cmd="$3" expected_exit="$4" expected_output="$5" desc="$6"
    ((TOTAL++))
    cmd=$(echo "$cmd" | sed -E 's/^"//; s/"$//')
    local mini_output mini_exit
    mini_output=$($EXPECT_RUNNER "$MINISHELL_PATH" "$cmd" 2>&1)
    mini_exit=$?
    mini_output=$(echo "$mini_output" | tr -d '\r' | sed '/^exit$/d' | sed -E 's/^[ \t]+|[ \t]+$//g')
    expected_output=$(echo "$expected_output" | tr -d '\r' | sed -E 's/^[ \t]+|[ \t]+$//g')
    if [[ "$mini_output" == "$expected_output" && "$mini_exit" -eq "$expected_exit" ]]; then
        ((PASS++))
        BRIEF_RESULTS+=("$(printf "%-4s %-30s %s" "$id" "$desc" "${GREEN}PASS${RESET}")")
    else
        ((FAIL++))
        BRIEF_RESULTS+=("$(printf "%-4s %-30s %s" "$id" "$desc" "${RED}FAIL${RESET}")")
        FAIL_DETAILS+=("$(cat <<EOF
${id} ${RED}FAIL${RESET}
🔎 Detalhes do teste $id:
Comando: $cmd
Esperado: [$expected_exit] $expected_output
Obtido:   [$mini_exit] $mini_output
EOF
)")
    fi
    show_progress_bar "$TOTAL" "$TOTAL_TESTS"
}

echo "${CYAN}────────────────────────────────────────────────────────────────────────────────────────────────────────────────────${RESET}"
echo "🧪 Testing Minishell vs Real Shell"
echo "${CYAN}────────────────────────────────────────────────────────────────────────────────────────────────────────────────────${RESET}"

TOTAL_TESTS=$(grep -vc '^id' "$TESTS_FILE")

while IFS=',' read -r id category cmd expected_exit expected_output desc; do
    [[ "$id" == "id" || -z "$id" ]] && continue
    run_test "$id" "$category" "$cmd" "$expected_exit" "$expected_output" "$desc"
done < "$TESTS_FILE"

echo -e "\n\n${CYAN}📋 Resumo de Todos os Testes (PASS/FAIL)${RESET}"
echo "${CYAN}────────────────────────────────────────────────────────────────────────────────────────────────────────────────────${RESET}"
print_in_columns "${BRIEF_RESULTS[@]}"

if (( FAIL > 0 )); then
    echo -e "\n${CYAN}❌ Detalhes das Falhas${RESET}"
    echo "${CYAN}────────────────────────────────────────────────────────────────────────────────────────────────────────────────────${RESET}"
    print_detailed_failures_single "${FAIL_DETAILS[@]}"
fi

echo "${CYAN}────────────────────────────────────────────────────────────────────────────────────────────────────────────────────${RESET}"
printf "✅ %d PASSED | ❌ %d FAILED | TOTAL %d\n" "$PASS" "$FAIL" "$TOTAL"
echo "${CYAN}────────────────────────────────────────────────────────────────────────────────────────────────────────────────────${RESET}"
