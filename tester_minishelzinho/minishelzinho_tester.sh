#!/usr/bin/env bash
# Minishelzinho Tester (interativo, colorido e ao vivo)

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
RESULTS=()

run_test() {
    local id="$1" desc="$6" cmd="$3"
    ((TOTAL++))

    # remove aspas externas (CSV vem com "echo hello")
    cmd=$(echo "$cmd" | sed -E 's/^"//; s/"$//')

    local bash_output bash_exit mini_output mini_exit
    bash_output=$(bash -c "$cmd" 2>&1)
    bash_exit=$?

    mini_output=$($EXPECT_RUNNER "$MINISHELL_PATH" "$cmd" 2>&1)
    mini_exit=$?

    # normaliza saídas (remove CR, prompt, exit, trims)
    bash_output=$(echo "$bash_output" | tr -d '\r' | sed -E 's/^[ \t]+|[ \t]+$//g')
    mini_output=$(echo "$mini_output" | tr -d '\r' | sed -E 's/(^|\n)?minishell\$ ?//g' | sed '/^exit$/d' | sed -E 's/^[ \t]+|[ \t]+$//g')

    if [[ "$bash_output" == "$mini_output" && "$bash_exit" == "$mini_exit" ]]; then
        ((PASS++))
        RESULTS+=("$(printf "%-4s %-40s %s" "$id" "$desc" "${GREEN}PASS${RESET}")")
    else
        ((FAIL++))
        RESULTS+=("$(printf "%-4s %-40s %s" "$id" "$desc" "${RED}FAIL${RESET}")")
        # salva detalhes para FAILS
        echo -e "\n🔎 ${YELLOW}Detalhes do teste $id:${RESET}"
        echo "  ${YELLOW}Comando:${RESET} $cmd"
        echo "  ${YELLOW}Esperado:${RESET} [$bash_exit] $bash_output"
        echo "  ${YELLOW}Obtido:${RESET}   [$mini_exit] $mini_output"
    fi
}

# --- EXEC ---
echo "──────────────────────────────────────────────"
echo "🧪 Testing Minishell vs Bash (modo interativo)"
echo "──────────────────────────────────────────────"
while IFS=',' read -r id category cmd expected_exit expected_output desc; do
    [[ "$id" == "id" || -z "$id" ]] && continue
    run_test "$id" "$category" "$cmd" "$expected_exit" "$expected_output" "$desc"
done < "$TESTS_FILE"

echo "──────────────────────────────────────────────"
printf "%-4s %-40s %s\n" "ID" "DESCRIÇÃO" "RESULT"
printf "%-4s %-40s %s\n" "──" "──────────────────────────────" "──────"
for r in "${RESULTS[@]}"; do
    echo -e "$r"
done
echo "──────────────────────────────────────────────"
printf "✅ %d PASSED | ❌ %d FAILED | TOTAL %d\n" "$PASS" "$FAIL" "$TOTAL"
