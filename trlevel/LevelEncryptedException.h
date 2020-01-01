#pragma once

#include <exception>

namespace trlevel
{
    class LevelEncryptedException final : public std::exception
    {
    };
}
