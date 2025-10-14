#!/usr/bin/env bash
# Minishelzinho Tester

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

print_detailed_failures() {
    local arr=("$@")
    local arr_len=${#arr[@]}
    local cols=2
    local rows=$(( (arr_len + cols - 1) / cols ))

    for ((r = 0; r < rows; r++)); do
        local blocks=("" "")
        for ((c = 0; c < cols; c++)); do
            local idx=$(( c * rows + r ))
            if (( idx < arr_len )); then
                blocks[$c]="${arr[idx]}"
            fi
        done

        IFS=$'\n' read -rd '' -a left_lines <<< "$(echo -e "${blocks[0]}")"
        IFS=$'\n' read -rd '' -a right_lines <<< "$(echo -e "${blocks[1]}")"

        local max_lines=${#left_lines[@]}
        (( ${#right_lines[@]} > max_lines )) && max_lines=${#right_lines[@]}

        printf "%-70s     %-85s\n" "|-----------------------------------------------------------------|" "|--------------------------------------------------------------------------------|"
        for ((i = 0; i < max_lines; i++)); do
            local left="${left_lines[i]:-|}"
            local right="${right_lines[i]:-|}"
            printf "%-70s     %-85s\n" "$left" "$right"
        done
        printf "%-70s     %-85s\n\n" "|-----------------------------------------------------------------|" "|--------------------------------------------------------------------------------|"
    done
}

show_progress_bar() {
    local current=$1
    local total=$2
    local width=50
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
${id}                                  ${RED}FAIL${RESET}
🔎 Detalhes do teste $id:
Comando: $cmd
Esperado: [$expected_exit] $expected_output
Obtido:   [$mini_exit] $mini_output
EOF
)")
    fi
    show_progress_bar "$TOTAL" "$TOTAL_TESTS"
}

# - EXECUÇÃO
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
    print_detailed_failures "${FAIL_DETAILS[@]}"
fi

echo "${CYAN}────────────────────────────────────────────────────────────────────────────────────────────────────────────────────${RESET}"
printf "✅ %d PASSED | ❌ %d FAILED | TOTAL %d\n" "$PASS" "$FAIL" "$TOTAL"
echo "${CYAN}────────────────────────────────────────────────────────────────────────────────────────────────────────────────────${RESET}"
