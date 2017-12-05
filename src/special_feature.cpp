#include "special_feature.hpp"

const SpecialFeature * const SpecialFeature::get(const SpecialFeature::Type type) {
    return &all.at(type);
}

const std::map<const SpecialFeature::Type, const SpecialFeature> SpecialFeature::all = {
    { SpecialFeature::Type::TreasureRoom, SpecialFeature(SpecialFeature::Type::TreasureRoom) },
    { SpecialFeature::Type::CircularRoom, SpecialFeature(SpecialFeature::Type::CircularRoom) },
    { SpecialFeature::Type::ShrineRoom, SpecialFeature(SpecialFeature::Type::ShrineRoom) },
    { SpecialFeature::Type::WishingWellRoom, SpecialFeature(SpecialFeature::Type::WishingWellRoom) },
    { SpecialFeature::Type::ShopRoom, SpecialFeature(SpecialFeature::Type::ShopRoom) }
};
