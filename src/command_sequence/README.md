# Command Sequence

**DON'T** modify the files in this folder directly.

When a user creates a command sequence with `createCommandSequence` mutation, we serialize the command sequence and store it in this directory.

We want to validate each command sequence before it is uplinked to the OBC, and so the files in this directory are tracked by Git.

To make it easier to work with the command sequence, I have defined helper functions `readJsonFile` and `writeJsonFile` which return a promise.

You can access a command sequence by its Id which is returned when the sequence is created. Given the id of a command sequence you can access using `src/command_sequence/__id__.json` path.
