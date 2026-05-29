# Final Reflection

CIS 25 - Topple the Tower

---

## Scope Statement (written before implementation)

### Feature status from original plan


| Feature                                                      | Status                |
| ------------------------------------------------------------ | --------------------- |
| Single battle (Hero vs. Enemy, full card/status/deck system) | Done                  |
| Battle rewards (gold, random relic, pick a card)             | Done                  |
| Tower map / run structure (single path of fights)            | Done                  |
| Relic passive effects                                        | Done                  |
| Additional heroes beyond Ironknight                          | Done                  |
| ASCII battle animations                                      | Done (bonus)          |
| Save / load                                                  | Planned - not started |
| Graphical UI                                                 | Planned - not started |


### What I'm building for this submission

Tower map: instead of a single battle, the player fights through a sequence of rooms on a fixed path. Each room has a different enemy. Winning the last boss room wins the game.

Relic passive effects: relics were already in the codebase with names and descriptions but didn't do anything. Each one now has a real effect tied into the battle system.

Assassin hero: a second playable character with her own starter deck, card pool, starting relic, and ASCII sprites. Hero selection screen added at the start of the game.

ASCII battle animations: sprites for both heroes and all enemy tiers, with different poses for attack, skill, and power cards.

---

## Prompt 1: Plan vs. Reality

> Refer to above table for updated planned features / status.

I originally wanted to create a game with gameplay very similar to "Slay the Spire," the game "Topple the Tower" is based off of. I was not able to quite achieve the vision I had for the project, but I was able to achieve a fully functional game from start to win/lose. This project was very difficult for me because of the time constraint and the vast scope. The amount of classes needed for full implementation is dizzying, and there is tons of custom logic to go along with them. I am glad that the game is playable and has a few working features, even if it's incomplete.

For the final part, I planned to do the tower map and relic effects if I had time. I was able to implement both at a basic level, with the map having a 3-part linear structure. The difficulty of the battles is hardcoded as random `Basic` -> random `Elite` -> random `Boss`. The map ended up being more complex to implement correctly than I expected. I thought it would mostly just be a container of battles, but to do it right it needs all the room types working, a path generation algorithm, and proper difficulty balancing, all of which are themselves big features. In order to function like the full game, the map would need to be a randomly generated graph structure, with balanced pathing and various rooms. Currently, there are placeholders for the rooms besides `BattleRoom`, but none of the other rooms (such as `CampfireRoom`, `EventRoom`, `TreasureRoom`) are implemented, and some of the battle logic still lives in `Room`. Basically, the map works, but it's a more simplified version of the map that's in the real game. In order to fully make the map, other features have to be completed, such as all the different kinds of `Room`, and also an algorithm to randomly generate a directional graph with constraints that makes sense as a map.

For the stretch goal, I implemented a second playable hero, `Assassin`. A lot of the structure of the `Assassin` class was based off of the preexisting `Ironknight` since that was the first class implemented, so a lot of the patterns used to make the new hero functional were repeated (adding hero-specific cards and attributes). 

The scope grew more than I expected and I realized that there were a lot of moving pieces in the game to make it fully functional, so a lot of extended features are still on the to do list. There are hundreds more unique components that are not yet in the game, such as much more cards, more heroes and enemies, and more mechanics.

I added ASCII battle animations to make the game more interesting to look at. I tried to mimic a working screen on the terminal by clearing terminal on each print/render, so that the components didn't jump after each action, which gives the illusion of a screen animating. The ASCII art is very basic and I wanted to eventually have working graphics, but I realized it would be very difficult to implement, making it out of scope for this project. I picked out some background and character sprites with animations on itch.io, so maybe if I have some time in the future I can continue extending the functionality of this project and implementing a graphical interface using a cursor.

---

## Prompt 2: Design Decisions You Would Change

Card descriptions are static strings set in the constructor, so they always show the base damage even when `Strength` or `Weak` is active. The damage math is correct but the displayed number is wrong. I would compute the description at render time instead. I'd also rethink how relics work. Right now `Hero` has a big switch statement that checks the relic type at each trigger. It works but every new trigger requires editing `Hero`. It would be cleaner if each relic knew its own effects. `Room` needs to be updated so all the battle logic is in `BattleRoom`. Right now `Room` has a `run()` method that handles combat directly instead of delegating to `BattleRoom`, a holdover from when Battle was the only Room, which still needs to be updated.

---

## Prompt 3: What You Learned

In terms of design, I got a lot more practice with class structure while working on this project. For instance, using a `Hero*` pointer so both heroes run through the same game loop without any if/else branching suited the concept of inheritance that we learned in class. The same pattern applied to `Card`, `Enemy`, and `Room`, each with their own subclass hierarchies so different types could share base behavior while overriding what was specific to them, which is good practical use of object oriented programming. For example, all enemies inherit from a base `Enemy` class but override their attack patterns, and all cards inherit from `Card` but override `play()` with their own effect. 

I also got more comfortable with virtual functions and knowing when to override vs. just let the base class handle it. 

Technically, I learned how to manage a project across multiple files and directories with CMake, earlier assignments were small enough that everything fit in one or two files, this one had headers, source files, and tests all organized into subdirectories, and I had to understand how `target_include_directories` and linking worked to keep it building. 

Concerning process, I learned about working on a more complex project and how to plan for it and do the workflow. I realized while working that some things took much longer than anticipated, especially when there's ambiguity or an unclear plan. I became more familiar with git and working on a repo and how using branches helps with isolating features, and how that would be useful for a large project that many people collaborate on. 

Finally, I learned about working with AI as a tool to improve efficiency in coding, and all the different ways AI can be leveraged to help improve code, as well as pitfalls such as hallucinations or mistakes in code generated.

---

## Prompt 4: What's Left to Finish

1. **Map graph structure.** The current path is a predetermined 3-step sequence with no branching, so every run's map is hardcoded, adding randomly generated branching maps for acts will make the game more interesting because the map is different every time, and user choice for which path to take affects their chances of success (e.g. choosing to fight too many enemies results in low health and possibly dying, but fighting too few enemies means having not enough strong cards and relics to be able to defeat stronger enemies); this is important for the roguelike aspect of the game and also makes it more important for the player to act strategically in order to not lose
2. **Non-battle rooms** (`CampfireRoom`, `EventRoom`, `TreasureRoom`, `ShopRoom`). These are all declared and stubbed but have no behavior yet, implementation tbd. Also, gold is currently unusable until shops exist
3. **Card upgrades and card removal, enemy status cards, curses** Core mechanics in the genre that let players improve their deck as the run progresses (removing cards means cycling through deck more frequently, adding cards means that eventual enemy status cards will be diluted in deck). Status and curse cards weaken the player (status cards exist only during battle they originated in, curses stay in player's deck until they are removed for gold)
4. **Ascensions** (difficulty levels) Provides replay value and a way to scale challenge for players who have beat the base game
5. **Save / load and run statistics.** Track performance across multiple runs, allows player to pause and return to a run
6. **More content** (cards, heroes, enemies), more variety makes runs feel different from each other, which is the core of the roguelike format. Hundreds of components present in the original game are not yet added to the project yet
7. **Graphical UI with sprite animations.** Would replace the terminal interface with actual graphics using a cursor, making the user experience have less friction and more enjoyable

---

## Prompt 5: Workflow Reflection

Working on a feature branch and writing commits as I went made it easy to track what changed. When something broke I could look at recent commits and figure out where it happened. I also caught a few things I wanted to fix just from reading the PR diff before merging. It felt natural to make commits periodically when working on features at natural stopping points such as when a class is implemented, or when the tests are written. Sometimes I would forget to make incremental commits and a big batch of code changes would all be in a single commit (for example, my `Implement Assassin class` commit), making the commit large and difficult to parse. I will keep in mind to remember to commit frequently when working on a Git repo in the future.

It is kind of a pain to make a PR because I have to write a whole new description for the PR and that takes a long time and seems redundant, but I understand why it is useful from the perspective of a reviewer. The PR description would help a reviewer quickly identify what was supposed to change in the PR so they can verify that the description matches the diff. 

If I were collaborating with another developer, the branch isolation would be very important in order to allow many people to work on the same codebase at the same time, without messing up the main branch or each other's branches. It would keep track of all the changes to the codebase and who wrote those changes. The review process is also more relevant because the reviewer (separate person from the author) basically makes sure that the changes in the PR look accurate and don't break anything. This is necessary because a reviewer might catch some details or bugs that the author missed. Self review would be less relevant/matter less, since that isn't a standard PR approval process. Documentation is also useful for collaboration so people can learn what the repo does and how to use it, as well as learn about it for the purposes of working on it.

---

## Prompt 6: AI Use

I used various AI tools to help with this project, including Github Copilot, ChatGPT, and Claude.ai. It was very helpful for bouncing ideas off of, autocompleting code, asking if something will work or not, and implementing code once it understood what the plan was. It was very good at refactoring existing code if a new feature was built on top of the existing code and some code organization had to change. It was also good at debugging and reviewing code. I reviewed everything before committing and corrected mistakes when they occured, which was pretty frequently. It sometimes suggested new feature implementations that did not fit with the existing code structure, which I had to give it additional context for it to fix the mistake. Sometimes, it would forget previous things it knew. I was very amazed at how much faster AI could write code compared to me writing it manually, but I also realized that because it made a lot of mistakes, very good understanding of what the code does and a very well-thought-out plan was very important to help AI work correctly. Sometimes getting AI up to speed on the existing code structure took a lot of back and forth and ended up taking longer than just writing the code myself would have. I made decisions about what to build and how the systems fit together. AI was more useful once the plan was already figured out, not as a self-directed planning tool that doesn't need programmer feedback. AI is a very useful tool but it's important to understand what it's doing.
