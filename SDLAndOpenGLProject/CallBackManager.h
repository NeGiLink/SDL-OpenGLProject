#pragma once
#include "Typedefs.h"
#include "StandardLibrary.h"

//�R�[���o�b�N�������J�v�Z������������
//C#��event Action�����ɍ쐬
template<typename Signature>
class Event;

template<typename Ret, typename... Args>
class Event<Ret(Args...)> {
public:
    using Handler = std::function<Ret(Args...)>;

    void Add(const Handler& handler) {
        handlers.push_back(handler);
    }

    void Invoke(Args... args) {
        for (auto& handler : handlers) {
            handler(args...);
        }
    }

private:
    std::vector<Handler> handlers;
};