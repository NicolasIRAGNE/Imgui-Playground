/**
 * @file fs.h
 * @author Nicolas IRAGNE (nicolas.iragne@alyce.fr)
 * @brief Provides some filesystem utilities
 * @date 2023-03-04
 *
 * @copyright Copyright Alyce (c) 2023
 */

#pragma once

#include <filesystem>
#include <map>
#include <vector>

namespace rlfs
{

struct Entry
{
    std::filesystem::path           path;
    std::filesystem::file_time_type last_write_time;
    std::uintmax_t                  size { 0 };
    bool                            computed { false };
    std::filesystem::file_type      type { std::filesystem::file_type::none };

    explicit Entry(const std::filesystem::path& path);
    void compute(bool force = false);
};

/**
 * @brief A file system context. Provides some utilities to work with the filesystem.
 */
class Context
{
public:
    Context()  = default;
    ~Context() = default;

    /**
     * @brief Get the list of entries in the current working directory
     *
     * @return std::vector<Entry> The list of entries
     */
    std::vector<Entry> get_entries() const;

    /**
     * @brief Set the current working directory
     *
     * @param path The path to the directory
     * @return true If the directory was successfully changed
     */
    bool set_working_directory(const std::filesystem::path& path);

    /**
     * @brief Get the current working directory
     *
     * @return std::filesystem::path The path to the current working directory
     */
    std::filesystem::path get_working_directory() const;

private:
    void                                                compute_entries();
    std::filesystem::path                               m_working_directory {};
    bool                                                m_entries_computed { false };
    std::map<std::filesystem::path, std::vector<Entry>> m_cache {};
};

} // namespace rfs