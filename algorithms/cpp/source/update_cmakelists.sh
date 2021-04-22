#! /bin/bash
#
# update_cmakelists.sh
# Copyright (C) 2021 StrayWarrior <i@straywarrior.com>

current_cases=($(cat CMakeLists.txt |grep -E "^leetcode_add_case" |cut -d '(' -f 2 |tr -d '()' |sort))
updated_cases=($(find . -name '*.cpp' |cut -d '/' -f 2 |cut -d '.' -f 1 |sort))
added_cases=($(comm -13 <(printf '%s\n' ${current_cases[@]}) <(printf '%s\n' ${updated_cases[@]})))
for case_name in ${added_cases[@]}; do
    echo "Add case: $case_name"
    echo "leetcode_add_case($case_name)" >> CMakeLists.txt
done
