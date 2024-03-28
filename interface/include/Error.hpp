/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <stdexcept>
#include <string>
#include <iostream>

#define NEW_EXCEPTION(name)                                                        \
    class name : public ArcadeException                                                   \
    {                                                                                  \
    public:                                                                            \
        name(std::string const &message) noexcept     \
            : ArcadeException(message) {}                                           \
    };

namespace arcade
{
    class ArcadeException : public std::exception
    {
    public:
        ArcadeException(std::string const &message) noexcept
            : _message(message) {}

        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
    };

    NEW_EXCEPTION(NoWindowException)
    NEW_EXCEPTION(SdlNotInitializedException)
    NEW_EXCEPTION(SdlTtfNotInitializedException)
    NEW_EXCEPTION(SdlQuitException)
    NEW_EXCEPTION(SdlRendererException)
    NEW_EXCEPTION(SdlNullSurfaceException)
    NEW_EXCEPTION(BadModuleTypeException)
    NEW_EXCEPTION(OpendirException)
    NEW_EXCEPTION(NoModuleLoadedException)
}


#endif /* !ERROR_HPP_ */
