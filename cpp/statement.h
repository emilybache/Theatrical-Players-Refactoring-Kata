#pragma once

#include "json.hpp"

std::string statement(
    const nlohmann::json& invoice,
    const nlohmann::json& plays);
