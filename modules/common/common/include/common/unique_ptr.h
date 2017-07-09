#ifndef PROJECT_UNIQUE_PTR_H
#define PROJECT_UNIQUE_PTR_H

namespace ifx{

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

}

#endif //PROJECT_UNIQUE_PTR_H
