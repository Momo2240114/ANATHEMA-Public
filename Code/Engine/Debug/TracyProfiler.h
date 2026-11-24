#pragma once

#include "Engine/Core/BuildConfig.h"

#if BS_ENABLE_TRACY

// Tracy有効時は実マクロへ展開し、CPU/GPUのスコープ計測をコード側から統一的に呼べるようにする。
#include <tracy/Tracy.hpp>
#include <tracy/TracyD3D11.hpp>
#include <cstring>

#if defined(BS_BUILD_DEBUG)
// 詳細GPUスコープはDebugビルドだけ有効にして、Release時の計測オーバーヘッドを抑える。
#define BS_PROFILE_DETAILED_ENABLED 1
#else
#define BS_PROFILE_DETAILED_ENABLED 0
#endif

#define BS_PROFILE_SCOPE(name_) ZoneScopedN(name_)
#define BS_PROFILE_FUNCTION() ZoneScoped
#define BS_PROFILE_FRAME_MARK() FrameMark
#define BS_PROFILE_PLOT(name_, ...) TracyPlot(name_, static_cast<double>((__VA_ARGS__)))
#define BS_PROFILE_TEXT(text_, size_) TracyMessage(text_, size_)

#define BS_PROFILE_SCOPE_DYNAMIC(name_) \
    ZoneScoped;                         \
    ZoneName(name_, std::strlen(name_))

// D3D11のGPU計測コンテキスト型。Tracy無効時はvoid*へ落とすため、呼び出し側の型分岐を避けられる。
using BS_PROFILE_GPU_CONTEXT_HANDLE = TracyD3D11Ctx;

#define BS_PROFILE_GPU_CONTEXT(device_, deviceContext_) \
    TracyD3D11Context(device_, deviceContext_)

#define BS_PROFILE_GPU_CONTEXT_NAME(context_, name_) \
    do                                               \
    {                                                \
        if ((context_) != nullptr)                   \
        {                                            \
            TracyD3D11ContextName(                   \
                context_,                            \
                name_,                               \
                static_cast<uint16_t>(std::strlen(name_))); \
        }                                            \
    } while (false)

#define BS_PROFILE_GPU_DESTROY(context_) \
    do                                   \
    {                                    \
        if ((context_) != nullptr)       \
        {                                \
            TracyD3D11Destroy(context_)  \
        }                                \
    } while (false)

#define BS_PROFILE_GPU_FRAME_MARK(context_) \
    do                                      \
    {                                       \
        if ((context_) != nullptr)          \
        {                                   \
            TracyD3D11Collect(context_)     \
        }                                   \
    } while (false)

#define BS_PROFILE_GPU_SCOPE(context_, name_) \
    TracyD3D11NamedZone(                      \
        context_,                             \
        TracyConcat(__bsTracyGpuZone, __LINE__), \
        name_,                                \
        (context_) != nullptr)

#define BS_PROFILE_GPU_NAMED_SCOPE(context_, variableName_, name_) \
    TracyD3D11NamedZone(context_, variableName_, name_, (context_) != nullptr)

#if BS_PROFILE_DETAILED_ENABLED
#define BS_PROFILE_GPU_DETAILED_SCOPE(context_, name_) \
    BS_PROFILE_GPU_SCOPE(context_, name_)
#else
#define BS_PROFILE_GPU_DETAILED_SCOPE(context_, name_)
#endif

#else

// Tracy無効時は全マクロを空にし、計測コードを残したままビルドできるようにする。
#define BS_PROFILE_SCOPE(name_)
#define BS_PROFILE_FUNCTION()
#define BS_PROFILE_FRAME_MARK()
#define BS_PROFILE_PLOT(name_, ...)
#define BS_PROFILE_TEXT(text_, size_)

#define BS_PROFILE_SCOPE_DYNAMIC(name_)
#define BS_PROFILE_DETAILED_ENABLED 0

using BS_PROFILE_GPU_CONTEXT_HANDLE = void*;

#define BS_PROFILE_GPU_CONTEXT(device_, deviceContext_) nullptr
#define BS_PROFILE_GPU_CONTEXT_NAME(context_, name_)
#define BS_PROFILE_GPU_DESTROY(context_)
#define BS_PROFILE_GPU_FRAME_MARK(context_)
#define BS_PROFILE_GPU_SCOPE(context_, name_)
#define BS_PROFILE_GPU_NAMED_SCOPE(context_, variableName_, name_)
#define BS_PROFILE_GPU_DETAILED_SCOPE(context_, name_)

#endif
