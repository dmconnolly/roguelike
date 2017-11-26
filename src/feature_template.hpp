#pragma once
#ifndef FEATURE_TEMPLATE_HPP
#define FEATURE_TEMPLATE_HPP

#include <map>

class FeatureTemplate {
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

    FeatureTemplate(const FeatureTemplate::Type type) {
        switch(type) {
            case FeatureTemplate::Type::TreasureRoom:
                break;
            case FeatureTemplate::Type::CircularRoom:
                break;
            case FeatureTemplate::Type::ShrineRoom:
                break;
            case FeatureTemplate::Type::WishingWellRoom:
                break;
            case FeatureTemplate::Type::ShopRoom:
                break;
        }
    }

    ~FeatureTemplate() = default;
    FeatureTemplate& operator=(const FeatureTemplate&) = delete;

    static const FeatureTemplate * const get(const FeatureTemplate::Type feature_template);

private:
    static const std::map<const FeatureTemplate::Type, const FeatureTemplate> all;
};

#endif /* FEATURE_TEMPLATE_HPP */
