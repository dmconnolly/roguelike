#pragma once
#ifndef FEATURE_TEMPLATE_HPP
#define FEATURE_TEMPLATE_HPP

#include <map>

#include "feature.hpp"

class SpecialFeature : Feature {
public:
    unsigned width;
    unsigned height;

    enum class Type : unsigned char {
        TreasureRoom,
        CircularRoom,
        ShrineRoom,
        WishingWellRoom,
        ShopRoom
    };

    SpecialFeature(const SpecialFeature::Type type) {
        switch(type) {
            case SpecialFeature::Type::TreasureRoom:
                break;
            case SpecialFeature::Type::CircularRoom:
                break;
            case SpecialFeature::Type::ShrineRoom:
                break;
            case SpecialFeature::Type::WishingWellRoom:
                break;
            case SpecialFeature::Type::ShopRoom:
                break;
        }
    }

    ~SpecialFeature() = default;
    SpecialFeature& operator=(const SpecialFeature&) = delete;

    static const SpecialFeature * const get(const SpecialFeature::Type feature_template);

private:
    static const std::map<const SpecialFeature::Type, const SpecialFeature> all;
};

#endif /* FEATURE_TEMPLATE_HPP */
