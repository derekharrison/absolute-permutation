/*
 * main.cpp
 *
 *  Created on: Jul 19, 2021
 *      Author: d-w-h
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>

int min(int a, int b) {
    int result;

    if(a < b) { result = a; }
    else { result = b; }

    return result;
}

bool is_abs_perm(std::vector<int> &min_abs_perm, int k) {

    bool result = true;
    int size_perm = min_abs_perm.size();

    for(int i = 0; i < size_perm; ++i) {
        if(abs(min_abs_perm[i] - (i + 1)) != k) {
            result = false;
        }
    }

    return result;
}

void get_lex_min(std::vector<int> array_ref, std::vector<int> &min_abs_perm, int k) {

    int size_ref = array_ref.size();
    int size_min_abs_perm = min_abs_perm.size();
    bool min_abs_perm_is_lex_smaller = false;
    bool smallest_lex_perm_is_known = false;
    int min_size = min(size_ref, size_min_abs_perm);

    bool perm_is_not_abs = false;
    if(!perm_is_not_abs) {
        min_abs_perm = array_ref;
        perm_is_not_abs = true;
    }

    int index_track = 0;
    while(!smallest_lex_perm_is_known && index_track < min_size) {
        if(array_ref[index_track] > min_abs_perm[index_track]) {
            min_abs_perm_is_lex_smaller = true;
            smallest_lex_perm_is_known = true;
        }
        else if(array_ref[index_track] < min_abs_perm[index_track]) {
            min_abs_perm_is_lex_smaller = false;
            smallest_lex_perm_is_known = true;
        }
        else { index_track++; }
    }

    if(!min_abs_perm_is_lex_smaller) {
        min_abs_perm = array_ref;
    }

    min_abs_perm = array_ref;

}

void determine_min_abs_perm(std::vector<int> track_indices,
                            std::vector<int> &min_abs_perm,
                            int num_elem,
                            int n,
                            int k,
                            bool &abs_perm_present) {

    int size_vector = track_indices.size();
    int min_index = 1;
    int max_index = n;

    for(int i = min_index; i <= max_index; ++i) {
        bool index_not_used = true;
        for(int j = 0; j < size_vector; ++j) {
            index_not_used = index_not_used && track_indices[j] != i;
        }
        if(index_not_used) {
            std::vector<int> tracker = track_indices;
            tracker.push_back(i);
            int num_elem2 = num_elem + 1;

            if(num_elem2 == n) {
                bool perm_is_abs = is_abs_perm(tracker, k);
                if(perm_is_abs) {
                    get_lex_min(tracker, min_abs_perm, k);
                    abs_perm_present = true;
                }
            }
            else {
                determine_min_abs_perm(tracker, min_abs_perm, num_elem2, n, k, abs_perm_present);
            }
        }
    }
}

std::vector<int> absolute_permutation(int n, int k) {
    std::vector<int> track_indices;
    std::vector<int> min_abs_perm;

    for(int i = 0; i < n; ++i) {
        min_abs_perm.push_back(i + 1);
    }

    bool there_is_an_abs_perm = false;
    determine_min_abs_perm(track_indices, min_abs_perm, 0, n, k, there_is_an_abs_perm);

    std::vector<int> result;

    if(!there_is_an_abs_perm) { result.push_back(-1); }
    else { result = min_abs_perm; }

    return result;

}

int main(int argc, char* argv[]) {

    int n = 10; //Size of array
    int k = 1; //Absolute constant

    //Get smallest lexicographic permutation array
    std::vector<int> result = absolute_permutation(n, k);

    //Print results
    int size_result = result.size();
    for(int i = 0; i < size_result; ++i) {
        std::cout << result[i] << " ";
    }

    std::cout << std::endl;
    std::cout << "done" << std::endl;

    return 0;
}

