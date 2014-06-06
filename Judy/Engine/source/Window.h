
#pragma once

namespace Judy
{
    class JWindow
    {
    public:
        static JWindow* Create();

        void show();

        virtual void SetContext() = 0;
        virtual void Swap() = 0;

    };
}
