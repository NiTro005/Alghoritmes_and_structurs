// Copyright 2024 Kita Trofimov
#pragma once
#include "../lib_string/cstring.h"
#include "../lib_stack/stack.h"
#include "../lib_list/tlist.h"
#include "../lib_list/tnode.h"
bool IsCorrect(const CString& str);
template<typename T>
bool RabbitTurtleCycleList(const TList<T>& list);
template bool RabbitTurtleCycleList<int>(const TList<int>& list);

template<typename T>
bool UpheavalPointerCycleList(const TList<T>& list);
template bool UpheavalPointerCycleList<int>(const TList<int>& list);
