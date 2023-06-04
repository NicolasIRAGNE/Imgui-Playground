/**
 * @file fs.cpp
 * @author Nicolas IRAGNE (nicolas.iragne@alyce.fr)
 * @brief Implementation of the filesystem utilities
 * @date 2023-03-05
 *
 * @copyright Copyright Alyce (c) 2023
 */

#include <greeter/fs.h>

namespace rlfs
{

Entry::Entry(const std::filesystem::path& path)
    : path(path)
{
}

void Entry::compute(bool force)
{
    if (computed && !force)
    {
        return;
    }
    last_write_time = std::filesystem::last_write_time(path);
    size            = std::filesystem::file_size(path);
    type            = std::filesystem::status(path).type();
    computed        = true;
}

std::vector<Entry> Context::get_entries() const
{
    if (m_cache.contains(m_working_directory))
    {
        return m_cache.at(m_working_directory);
    }
    return {};
}

void Context::compute_entries()
{
    std::vector<Entry> entries;
    for (const auto& entry : std::filesystem::directory_iterator(m_working_directory))
    {
        auto e = Entry(entry.path());
        e.compute();
        entries.push_back(std::move(e));
    }
    m_cache[m_working_directory] = entries;
}

bool Context::set_working_directory(const std::filesystem::path& path)
{
    if (!(std::filesystem::exists(path) && std::filesystem::is_directory(path)))
    {
        return false;
    }
    m_working_directory = path;
    if (!(m_cache.contains(m_working_directory)))
    {
        compute_entries();
    }
    return true;
}

std::filesystem::path Context::get_working_directory() const
{
    return m_working_directory;
}

} // namespace rlfs