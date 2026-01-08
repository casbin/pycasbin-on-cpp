#!/usr/bin/env python3
"""
Basic example demonstrating pycasbin-on-cpp usage
"""

import os
from pycasbin_cpp import Enforcer

def main():
    # Get the directory of this script
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # Initialize enforcer with model and policy files
    model_path = os.path.join(script_dir, 'rbac_model.conf')
    policy_path = os.path.join(script_dir, 'rbac_policy.csv')
    
    e = Enforcer(model_path, policy_path)
    
    print("=== pycasbin-on-cpp Basic Example ===\n")
    
    # Test enforcement
    print("Testing enforce():")
    print(f"  alice, data1, read: {e.enforce(['alice', 'data1', 'read'])}")
    print(f"  alice, data1, write: {e.enforce(['alice', 'data1', 'write'])}")
    print(f"  alice, data2, read: {e.enforce(['alice', 'data2', 'read'])}")
    print(f"  alice, data2, write: {e.enforce(['alice', 'data2', 'write'])}")
    print(f"  bob, data2, write: {e.enforce(['bob', 'data2', 'write'])}")
    print(f"  bob, data1, read: {e.enforce(['bob', 'data1', 'read'])}")
    
    print("\nTesting get_roles_for_user():")
    print(f"  alice's roles: {e.get_roles_for_user('alice')}")
    print(f"  bob's roles: {e.get_roles_for_user('bob')}")
    
    print("\nTesting get_users_for_role():")
    print(f"  data2_admin role users: {e.get_users_for_role('data2_admin')}")
    
    print("\nTesting get_policy():")
    policies = e.get_policy()
    for policy in policies:
        print(f"  {policy}")
    
    print("\nAdding new policy: p, bob, data1, read")
    e.add_policy(['bob', 'data1', 'read'])
    
    print("Testing after adding policy:")
    print(f"  bob, data1, read: {e.enforce(['bob', 'data1', 'read'])}")
    
    print("\nAll tests completed!")

if __name__ == '__main__':
    main()
