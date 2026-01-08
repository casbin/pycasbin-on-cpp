/*
 * Copyright 2021 The casbin Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "casbin/casbin.h"

namespace py = pybind11;
using namespace casbin;

// Helper function to convert Python args to DataVector for Enforce
DataVector make_data_vector(const std::vector<std::string>& args) {
    DataVector data_vec;
    for (const auto& arg : args) {
        data_vec.push_back(arg);
    }
    return data_vec;
}

// Helper function to convert PoliciesValues to Python list
std::vector<std::vector<std::string>> policies_values_to_vector(const PoliciesValues& policies) {
    std::vector<std::vector<std::string>> result;
    for (const auto& policy : policies) {
        result.push_back(policy);
    }
    return result;
}

PYBIND11_MODULE(_pycasbin_cpp, m) {
    m.doc() = "pycasbin-on-cpp: High-performance Python bindings for casbin-cpp";

    // Enforcer class
    py::class_<Enforcer, std::shared_ptr<Enforcer>>(m, "Enforcer")
        // Constructors
        .def(py::init<>())
        .def(py::init<const std::string&, const std::string&>(),
             py::arg("model_path"), py::arg("policy_file"))
        .def(py::init<const std::string&>(),
             py::arg("model_path"))
        
        // Enforcement
        .def("enforce", [](Enforcer& e, const std::vector<std::string>& params) {
            DataVector data = make_data_vector(params);
            return e.Enforce(data);
        }, py::arg("params"))
        
        .def("enforce_ex", [](Enforcer& e, const std::vector<std::string>& params) {
            DataVector data = make_data_vector(params);
            std::vector<std::string> explain;
            bool result = e.EnforceEx(data, explain);
            return py::make_tuple(result, explain);
        }, py::arg("params"))
        
        // Policy management
        .def("load_policy", &Enforcer::LoadPolicy)
        .def("save_policy", &Enforcer::SavePolicy)
        .def("clear_policy", &Enforcer::ClearPolicy)
        
        // Policy API
        .def("get_policy", [](Enforcer& e) {
            return policies_values_to_vector(e.GetPolicy());
        })
        .def("get_filtered_policy", [](Enforcer& e, int field_index, const std::vector<std::string>& field_values) {
            return policies_values_to_vector(e.GetFilteredPolicy(field_index, field_values));
        }, py::arg("field_index"), py::arg("field_values"))
        .def("has_policy", &Enforcer::HasPolicy,
             py::arg("params"))
        .def("add_policy", &Enforcer::AddPolicy,
             py::arg("params"))
        .def("add_policies", &Enforcer::AddPolicies,
             py::arg("rules"))
        .def("remove_policy", &Enforcer::RemovePolicy,
             py::arg("params"))
        .def("remove_policies", &Enforcer::RemovePolicies,
             py::arg("rules"))
        .def("remove_filtered_policy", &Enforcer::RemoveFilteredPolicy,
             py::arg("field_index"), py::arg("field_values"))
        .def("update_policy", &Enforcer::UpdatePolicy,
             py::arg("old_policy"), py::arg("new_policy"))
        
        // Grouping (role) policy API
        .def("get_grouping_policy", [](Enforcer& e) {
            return policies_values_to_vector(e.GetGroupingPolicy());
        })
        .def("get_filtered_grouping_policy", [](Enforcer& e, int field_index, const std::vector<std::string>& field_values) {
            return policies_values_to_vector(e.GetFilteredGroupingPolicy(field_index, field_values));
        }, py::arg("field_index"), py::arg("field_values"))
        .def("has_grouping_policy", &Enforcer::HasGroupingPolicy,
             py::arg("params"))
        .def("add_grouping_policy", &Enforcer::AddGroupingPolicy,
             py::arg("params"))
        .def("add_grouping_policies", &Enforcer::AddGroupingPolicies,
             py::arg("rules"))
        .def("remove_grouping_policy", &Enforcer::RemoveGroupingPolicy,
             py::arg("params"))
        .def("remove_grouping_policies", &Enforcer::RemoveGroupingPolicies,
             py::arg("rules"))
        .def("remove_filtered_grouping_policy", &Enforcer::RemoveFilteredGroupingPolicy,
             py::arg("field_index"), py::arg("field_values"))
        .def("update_grouping_policy", &Enforcer::UpdateGroupingPolicy,
             py::arg("old_rule"), py::arg("new_rule"))
        
        // RBAC API
        .def("get_roles_for_user", &Enforcer::GetRolesForUser,
             py::arg("name"), py::arg("domain") = std::vector<std::string>{})
        .def("get_users_for_role", &Enforcer::GetUsersForRole,
             py::arg("name"), py::arg("domain") = std::vector<std::string>{})
        .def("has_role_for_user", &Enforcer::HasRoleForUser,
             py::arg("name"), py::arg("role"))
        .def("add_role_for_user", &Enforcer::AddRoleForUser,
             py::arg("user"), py::arg("role"))
        .def("add_roles_for_user", &Enforcer::AddRolesForUser,
             py::arg("user"), py::arg("roles"))
        .def("delete_role_for_user", &Enforcer::DeleteRoleForUser,
             py::arg("user"), py::arg("role"))
        .def("delete_roles_for_user", &Enforcer::DeleteRolesForUser,
             py::arg("user"))
        .def("delete_user", &Enforcer::DeleteUser,
             py::arg("user"))
        .def("delete_role", &Enforcer::DeleteRole,
             py::arg("role"))
        
        // Permission management
        .def("add_permission_for_user", &Enforcer::AddPermissionForUser,
             py::arg("user"), py::arg("permission"))
        .def("delete_permission_for_user", &Enforcer::DeletePermissionForUser,
             py::arg("user"), py::arg("permission"))
        .def("delete_permissions_for_user", &Enforcer::DeletePermissionsForUser,
             py::arg("user"))
        .def("get_permissions_for_user", [](Enforcer& e, const std::string& user) {
            return policies_values_to_vector(e.GetPermissionsForUser(user));
        }, py::arg("user"))
        .def("has_permission_for_user", &Enforcer::HasPermissionForUser,
             py::arg("user"), py::arg("permission"))
        .def("get_implicit_roles_for_user", &Enforcer::GetImplicitRolesForUser,
             py::arg("name"), py::arg("domain") = std::vector<std::string>{})
        .def("get_implicit_permissions_for_user", [](Enforcer& e, const std::string& user, const std::vector<std::string>& domain) {
            return policies_values_to_vector(e.GetImplicitPermissionsForUser(user, domain));
        }, py::arg("user"), py::arg("domain") = std::vector<std::string>{})
        .def("get_implicit_users_for_permission", &Enforcer::GetImplicitUsersForPermission,
             py::arg("permission"))
        
        // Management API
        .def("get_all_subjects", &Enforcer::GetAllSubjects)
        .def("get_all_objects", &Enforcer::GetAllObjects)
        .def("get_all_actions", &Enforcer::GetAllActions)
        .def("get_all_roles", &Enforcer::GetAllRoles)
        
        // Configuration
        .def("enable_enforce", &Enforcer::EnableEnforce,
             py::arg("enable"))
        .def("enable_auto_save", &Enforcer::EnableAutoSave,
             py::arg("auto_save"))
        .def("enable_auto_build_role_links", &Enforcer::EnableAutoBuildRoleLinks,
             py::arg("auto_build_role_links"))
        .def("build_role_links", &Enforcer::BuildRoleLinks);

    // File adapter
    py::class_<FileAdapter, std::shared_ptr<FileAdapter>>(m, "FileAdapter")
        .def(py::init<const std::string&>(),
             py::arg("file_path"));

    // Version info
    m.attr("__version__") = "0.1.0";
}
