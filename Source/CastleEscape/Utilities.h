#pragma once
#include "Logging/LogMacros.h"

#define UNDEF_PTR(ptr, source) UE_LOG(LogTemp, Warning, TEXT("%s pointer not set on actor %s"), TEXT(ptr), source);
