#pragma once

// here is algorithm concept

template <typename Algo>
concept Algorithm = requires(Algo algorithm) {
    { algorithm.algorithm() };
};
