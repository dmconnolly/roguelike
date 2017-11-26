#include "feature_template.hpp"

const FeatureTemplate * const FeatureTemplate::get(const FeatureTemplate::Type type) {
    return &all.at(type);
}

const std::map<const FeatureTemplate::Type, const FeatureTemplate> FeatureTemplate::all = {
    { FeatureTemplate::Type::TreasureRoom, FeatureTemplate(FeatureTemplate::Type::TreasureRoom) },
    { FeatureTemplate::Type::CircularRoom, FeatureTemplate(FeatureTemplate::Type::CircularRoom) },
    { FeatureTemplate::Type::ShrineRoom, FeatureTemplate(FeatureTemplate::Type::ShrineRoom) },
    { FeatureTemplate::Type::WishingWellRoom, FeatureTemplate(FeatureTemplate::Type::WishingWellRoom) },
    { FeatureTemplate::Type::ShopRoom, FeatureTemplate(FeatureTemplate::Type::ShopRoom) }
};
