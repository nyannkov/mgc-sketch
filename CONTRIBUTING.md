# Contributing to mgc-sketch

Thank you for your interest in contributing to this project!

This document provides guidelines for contributing, with a focus on sample code contributions.  

## Types of Contributions

We welcome:

- Sample code contributions (see below for details)

We welcome other contributions, such as bug reports or suggestions for improvements related to this repository.  
However, issues related to the content of submodules are outside the scope of this repository.

Please note that responses from the maintainers may take some time due to work obligations.  
We appreciate your understanding and patience.

## Sample Code Contributions

If you would like to contribute sample code, please do so by creating a **separate repository** and adding it as a **git submodule**.

Please follow these guidelines:

- Use a separate repository for each sample and register it as a submodule
- Include a clear **license** for your sample code
- If your sample includes resources (e.g., fonts, images, sounds), make sure their **licenses are explicitly stated and allow redistribution**
- Do not include assets with unclear or restrictive licenses
- The contributor is **responsible** for the license and proper usage of all included resources
- We recommend using an **MIT-compatible license**, as the main project is licensed under the [MIT License](./LICENSE)
- Please **avoid including inappropriate content** in your sample

### Notes on Hardware and Software

- The hardware configuration (e.g., microcontroller, display, sound IC) is entirely up to you
- Please include enough documentation so that others can reproduce the environment if they wish
- The software structure is also completely up to the contributor

### Notes on mgc Versioning

Since **mgc is under active development**, breaking changes may occur in the future.  
Therefore, we recommend that you explicitly specify a commit hash or tag in the `ref` field under `import_libs` in your `mgc-sketch.yaml`.  
If omitted, the latest commit (`HEAD`) will be used, which may lead to unexpected behavior later.

Example:

```yaml
import_libs:
  - repo: ../../../libs/mgc
    ref: v0.4.0
    resources:
      - src/mgc -> ./src/libs/mgc
```

## Code Style

Since the sample code is independent, contributors are free to follow their own coding style and naming conventions.  

- **Please write comments in English**, unless there is a strong reason not to

## Pull Request Process

1. Fork this repository
2. Create a new branch (`git checkout -b feature/your-change`)
3. Make your changes and test them if necessary
4. Write meaningful commit messages
5. Open a pull request with a clear description of your changes

You do **not** need to create an issue before submitting a pull request for a sample.

## Licensing

This project is licensed under the [MIT License](./LICENSE).

By contributing to this repository, you agree to license your contributions under the same terms.  
Sample code submitted via submodules remains under the license defined by the respective contributor.  
Please ensure compatibility with the MIT License where applicable.
