# AI Prompts — Battle ASCII Art

---

## Sprites and Scene Layout

**Me:** add ascii art to the battle screen. ironknight on the left, enemy on the right. animate them when they take turns

**AI:** Added a `printScene()` function that renders two sprite columns side by side. Hero sprites face right, enemy sprites face left. Each is 5 lines tall. The scene prints at the top of every `printBattle` call.

For animation, `printBattle` takes a pose parameter. When the hero plays a card, the game shows the attack frame for 220ms before the normal state. When the hero ends their turn, the enemy attack frame shows for 220ms before `endHeroTurn` resolves damage — so you see the lunge before the HP changes.

Enemy sprites are tier-based: basic, elite, and boss each have a neutral and attack pose.

**Me:** make different animations for skill and defend on hero

**AI:** `CardType` was already on the `Card` class (`CARD_ATTACK`, `CARD_SKILL`, `CARD_POWER`). Added a `HeroAnim` enum and two new hero sprites:

- `CARD_ATTACK` → sword lunge (`]=======>`)
- `CARD_SKILL` → guard stance with shield (`]|[]`)
- `CARD_POWER` → arms-wide power stance (`\O/`)

The card type is peeked from the hand before `playCardFromHand` so the right animation plays regardless of the result.
