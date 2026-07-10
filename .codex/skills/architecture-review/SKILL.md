---
name: architecture-review
description: Review architecture before implementation.
---

Before proposing any implementation:

Understand:

- domain model
- responsibilities
- ownership
- dependencies
- feature boundaries

Look for:

- duplicated responsibilities
- incorrect abstractions
- cyclic dependencies
- hidden coupling
- violations of existing architecture

Always ask:

Can the existing architecture already support this feature?

Prefer extending existing systems.

Avoid parallel implementations.

When suggesting changes:

Describe trade-offs.

Explain why the proposal fits the current architecture.

Prefer minimal architectural impact.