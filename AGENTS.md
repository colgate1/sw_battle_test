# Project

This is a modern C++ project built with CMake.

## Workflow

Before editing code:

1. Inspect the existing architecture.
2. Reuse existing abstractions.
3. Explain the implementation plan.
4. Wait for approval before making large changes.

- ## Architecture principles

- Prefer extending existing systems over creating new ones.
- Avoid duplicate implementations.
- Do not rewrite unrelated code.
- Keep changes as small as possible.
- Preserve existing public APIs unless explicitly required.
- Follow the project's existing naming and coding style.

Treat the existing codebase as the primary source of truth.

Before implementing a feature:

- understand how similar functionality is already implemented;
- verify whether an existing abstraction can be extended;
- prefer consistency with the current architecture over introducing a technically cleaner but inconsistent solution.

Do not create new:

- managers;
- services;
- systems;
- helpers;
- utilities;
- wrappers;

unless the existing architecture cannot reasonably support the requested behavior.

Every new class must have a clear responsibility that cannot reasonably belong to an existing class.

## Dependencies

- Do not introduce new libraries without approval.
- Reuse existing project utilities.

## Validation

After implementation:

- Build the affected targets.
- Run relevant tests.
- Review the produced diff.
- Summarize:
    - changed files
    - assumptions
    - risks
    - unverified parts.