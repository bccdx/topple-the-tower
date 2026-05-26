# AI Collaboration Log

## Tools used
- GitHub Copilot Chat in Codespaces, Claude on the web

## A prompt that worked well
- Prompt: pasting the spec and asking to implement one class at a time
- Why it worked: it broke down the problem into small pieces and I could manually review each change, I gave it an overview of the project structure and existing functionality

## A prompt that did not work
- Prompt: asking to "implement battle rewards"
- What went wrong: the AI started designing the feature from scratch without knowing what classes already existed, and suggested a different interface than what fit the project
- How I recovered: wrote the spec first and started a new conversation with that as context, as well as gave information about existing project structure

## Code I rejected
- AI initially designed the relic as a player choice on the reward screen (type 4 to pick it, 0 to skip)
- Rejected it because relics in this game are automatic, the player always gets one after a fight and doesn't choose whether to take it
- Changed it to `awardRelic()` in prompt, which picks a random relic and gives it to the hero immediately, no input needed

## What I'd do differently next time
- Consider the edge cases on the spec, and use more specific language in prompt to get desired outcomes, make a spreadsheet of card and relic choices and convert to markdown