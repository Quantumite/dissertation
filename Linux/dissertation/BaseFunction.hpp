#pragma once

#include <vector>
#include <cstdint>

void BaseFunction1(std::vector<std::size_t>& iDataVector, std::size_t i);
void BaseFunction1(std::vector<unsigned char>& iDataVector, std::size_t i);

void BaseFunction3([[maybe_unused]] std::vector<std::size_t>& iDataVector, [[maybe_unused]] std::size_t i);
void BaseFunction3([[maybe_unused]] std::vector<unsigned char>& iDataVector, [[maybe_unused]] std::size_t i);

void BaseFunction4([[maybe_unused]] std::vector<std::size_t>& iDataVector, [[maybe_unused]] std::size_t i);
void BaseFunction4([[maybe_unused]] std::vector<unsigned char>& iDataVector, [[maybe_unused]] std::size_t i);

void BaseFunction5([[maybe_unused]] std::vector<std::size_t>& iDataVector, [[maybe_unused]] std::size_t i);
void BaseFunction5([[maybe_unused]] std::vector<unsigned char>& iDataVector, [[maybe_unused]] std::size_t i);