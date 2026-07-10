---
name: add-feature
description: Implement new gameplay features while preserving the existing architecture.
---

# Goal

Implement a new gameplay feature by integrating it into the existing architecture.

## Principles

Always prefer extending existing systems over introducing new abstractions.

If the existing architecture already solves the problem, integrate with it instead of creating a parallel implementation.

Avoid unnecessary complexity.

## Workflow

Before modifying any code:

1. Understand the feature request.
2. Inspect the repository.
3. Find similar mechanics.
4. Identify reusable systems.
5. Explain the implementation plan.
6. List expected modified files.
7. Identify ambiguities.

Do not edit code until the investigation is complete.

## During implementation

Reuse existing:

- entity model
- actions
- events
- combat pipeline
- damage pipeline
- targeting
- movement
- serialization
- configuration
- utilities

Keep the implementation small.

Avoid introducing:

- new managers
- new services
- new frameworks
- duplicated pipelines
- duplicated state

unless clearly required.

## Architecture

Keep feature-specific logic isolated.

Do not spread feature checks throughout unrelated systems.

Prefer composition over special cases.

## Validation

After implementation:

- verify the build
- run relevant tests
- inspect the diff
- report assumptions
- report remaining risks