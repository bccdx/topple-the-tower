# AI Collaboration Log

## Tools used

* GitHub Copilot Chat in Codespaces, Claude on the web

## A prompt that worked well

* Prompt: pasting the spec and asking to implement one class at a time
* Why it worked: it broke down the problem into small pieces and I could manually review each change, I gave it an overview of the project structure and existing functionality

## A prompt that did not work

* Prompt: asking to "implement battle rewards"
* What went wrong: the AI started designing the feature from scratch without knowing what classes already existed, and suggested a different interface than what fit the project
* How I recovered: wrote the spec first and started a new conversation with that as context, as well as gave information about existing project structure

## Code I rejected

* AI initially designed the relic as a player choice on the reward screen (type 4 to pick it, 0 to skip)
* Rejected it because relics in this game are automatic, the player always gets one after a fight and doesn't choose whether to take it
* Changed it to `awardRelic()` in prompt, which picks a random relic and gives it to the hero immediately, no input needed

## What I'd do differently next time

* Consider the edge cases on the spec, and use more specific language in prompt to get desired outcomes, make a spreadsheet of card and relic choices and convert to markdown

## Fresh-conversation review

Started a new conversation, pasted the spec and the new files from the PR diff and asked for a senior engineer style review. it caught a crash bug where the card name was being read before the bounds check in main.cpp, so typing a number bigger than the option count would go out of bounds. fixed that by checking the index first. also added a cap to the input parsing loop to prevent int overflow on large inputs, added a null guard in pickCard so calling it twice on the same slot doesn't push null into the deck, removed dead includes for Bash/Strike/Defend from Reward.cpp since they aren't in the reward pool, fixed stale path comments in the card headers from before the folder reorganization, and made empty input re-prompt instead of silently skipping. rejected the TwinStrike finding about hitting a dead target on the second hit since it said it was latent and only matters when on-kill effects exist, leaving it for later.
