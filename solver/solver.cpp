#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#define DLLEXPORT extern "C" __declspec(dllexport)

std::unordered_set<std::string> words;

std::string from_wchar(wchar_t *input) {
  std::wstring ws(input);
  std::string text(ws.begin(), ws.end());
  return text;
}

void remove_duplicates(std::vector<std::string> &list) {
  std::vector<std::string> result;
  for (auto item : list) {
    if (std::find(result.begin(), result.end(), item) == result.end()) {
      result.push_back(item);
    }
  }
  list = result;
}

std::vector<std::string> permutations(std::string text) {
  std::vector<std::string> result;
  std::sort(text.begin(), text.end());
  do {
    result.push_back(text);
  } while (std::next_permutation(text.begin(), text.end()));
  remove_duplicates(result);
  return result;
}

std::vector<std::string> subsets(std::string text) {
  std::vector<std::string> result;
  for (int i = 0; i < (1 << text.length()); i++) {
    std::string subset;
    for (int j = 0; j < text.length(); j++) {
      if (i & (1 << j)) {
        subset += text[j];
      }
    }
    if (subset.length() > 2) result.push_back(subset);
  }
  remove_duplicates(result);
  return result;
}

DLLEXPORT void init() {
  std::ifstream file("words.txt", std::ios::in);
  std::string word;
  while (file >> word) {
    words.insert(word);
  }
  file.close();
  return;
}

DLLEXPORT PyObject *__stdcall findall(wchar_t *input) {
  auto text = from_wchar(input);
  auto subsets = ::subsets(text);
  std::vector<std::string> list;
  auto gstate = PyGILState_Ensure();
  auto result = PyList_New(0);
  for (auto i : subsets) {
    auto perms = ::permutations(i);
    for (auto j : perms) {
      if (words.find(j) != words.end()) {
        list.push_back(j);
      }
    }
  }
  remove_duplicates(list);
  std::sort(list.begin(), list.end());
  for (auto i : list) {
    PyList_Append(result, Py_BuildValue("s", i.c_str()));
  }
  PyGILState_Release(gstate);
  return result;
}