# pycasbin-on-cpp

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

High-performance Python bindings for [casbin-cpp](https://github.com/casbin/casbin-cpp), providing blazing-fast authorization enforcement powered by C++.

## Overview

pycasbin-on-cpp wraps the casbin-cpp library to provide a Python interface with significantly better performance compared to the pure Python implementation. It maintains API compatibility with pycasbin while leveraging the speed of native C++ code.

## Features

- **High Performance**: C++ powered enforcement for maximum speed
- **Full RBAC Support**: Complete role-based access control implementation
- **Policy Management**: Comprehensive policy CRUD operations
- **Easy Integration**: Simple Python API compatible with pycasbin
- **Multiple Models**: Support for ACL, RBAC, ABAC, and custom models

## Installation

### Prerequisites

- Python 3.7+
- CMake 3.12+
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Git (for cloning with submodules)

### From Source

```bash
# Clone the repository with submodules
git clone --recursive https://github.com/casbin/pycasbin-on-cpp.git
cd pycasbin-on-cpp

# Install dependencies and build
pip install -e .
```

If you already cloned without `--recursive`:
```bash
git submodule update --init --recursive
pip install -e .
```

## Quick Start

```python
from pycasbin_cpp import Enforcer

# Initialize the enforcer with a model file and a policy file
e = Enforcer('path/to/model.conf', 'path/to/policy.csv')

# Check permissions
if e.enforce(['alice', 'data1', 'read']):
    print("Permission granted")
else:
    print("Permission denied")

# Add a policy
e.add_policy(['bob', 'data2', 'write'])

# Get all roles for a user
roles = e.get_roles_for_user('alice')
print(f"Alice's roles: {roles}")

# Save policies
e.save_policy()
```

## Examples

See the `examples/` directory for more detailed examples:

```bash
# Run the basic example
python examples/basic_example.py
```

## API Reference

### Enforcer

The main class for authorization enforcement.

#### Initialization

```python
# Create enforcer with model and policy file
e = Enforcer(model_path, policy_path)

# Create enforcer with only model file
e = Enforcer(model_path)
```

#### Enforcement API

- `enforce(params)`: Check if a request is allowed
- `enforce_ex(params)`: Check permission and get explanation

#### Policy Management

- `get_policy()`: Get all policies
- `add_policy(params)`: Add a policy rule
- `remove_policy(params)`: Remove a policy rule
- `update_policy(old_policy, new_policy)`: Update a policy rule

#### RBAC API

- `get_roles_for_user(user)`: Get roles for a user
- `get_users_for_role(role)`: Get users for a role
- `add_role_for_user(user, role)`: Add a role for a user
- `delete_role_for_user(user, role)`: Delete a role for a user
- `has_role_for_user(user, role)`: Check if user has role

#### Management API

- `get_all_subjects()`: Get all subjects
- `get_all_objects()`: Get all objects
- `get_all_actions()`: Get all actions
- `get_all_roles()`: Get all roles

## Model Configuration

pycasbin-on-cpp uses the same model configuration as pycasbin. Here's an example RBAC model:

```ini
[request_definition]
r = sub, obj, act

[policy_definition]
p = sub, obj, act

[role_definition]
g = _, _

[policy_effect]
e = some(where (p.eft == allow))

[matchers]
m = g(r.sub, p.sub) && r.obj == p.obj && r.act == p.act
```

## Performance

pycasbin-on-cpp provides significant performance improvements over pure Python implementations:

- **Enforcement**: 10-50x faster for typical use cases
- **Policy Loading**: 5-20x faster for large policy sets
- **Memory Usage**: More efficient memory utilization

## Development

### Building from Source

```bash
# Install development dependencies
pip install pybind11 setuptools wheel

# Build in development mode
python setup.py develop
```

### Running Tests

```bash
# Install test dependencies
pip install pytest

# Run tests
pytest tests/
```

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](https://github.com/casbin/casbin-cpp/blob/master/CONTRIBUTING.md) for details.

## License

This project is licensed under the Apache 2.0 License - see the [LICENSE](LICENSE) file for details.

## Links

- [Casbin Website](https://casbin.org)
- [Casbin C++ Repository](https://github.com/casbin/casbin-cpp)
- [pycasbin Repository](https://github.com/casbin/pycasbin)
- [Documentation](https://casbin.org/docs/en/overview)

## Acknowledgments

- Built on top of [casbin-cpp](https://github.com/casbin/casbin-cpp)
- Uses [pybind11](https://github.com/pybind/pybind11) for Python bindings