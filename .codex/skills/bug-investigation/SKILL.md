---
name: bug-investigation
description: Find the real root cause of gameplay or engine bugs.
---

# Goal

Find the root cause.

Never implement speculative fixes.

## Investigation

Before changing code:

1. Reproduce the issue.
2. Describe the expected behaviour.
3. Describe the actual behaviour.
4. Identify the execution flow.
5. Trace the state changes.
6. Identify where behaviour diverges.

Only after identifying the root cause propose a fix.

## Fix

Prefer fixing the cause instead of symptoms.

Avoid defensive programming that hides bugs.

Do not introduce unrelated refactoring.

## Report

Include:

- root cause
- why it happens
- affected systems
- proposed fix
- risks
- regression scenarios