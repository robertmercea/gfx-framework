#pragma once

#include "tema1/entities/effects/charge/charge.hpp"
#include "tema1/entities/effects/none/none.hpp"
#include "tema1/entities/properties/effect/effect_fwd.hpp"
#include "tema1/entities/effects/lifesteal/lifesteal.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include <unordered_map>
#include <memory>

namespace tema1 {
namespace globals {
namespace effects {

using EffectPtr = entities::EffectPtr;


const EffectPtr CHARGE = std::make_shared<entities::ChargeEffect>();
const EffectPtr LIFESTEAL = std::make_shared<entities::LifestealEffect>();
const EffectPtr NONE = std::make_shared<entities::NoneEffect>();

const std::unordered_map<globals::CardType, EffectPtr> CARD_EFFECTS = {
    {CardType::WIZARD, NONE},
    {CardType::DWARF, NONE},
    {CardType::KNIGHT, NONE},
    {CardType::MAGE, NONE},
    {CardType::HERO, NONE},
    {CardType::MINION, LIFESTEAL},
    {CardType::LEEROY_JENKINS, CHARGE},
};

} // namespace stats
} // namespace globals
} // namespace tema1
