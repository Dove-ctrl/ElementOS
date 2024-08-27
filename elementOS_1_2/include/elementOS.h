#ifndef ELEMENTOS_H_
#define ELEMENTOS_H_

#include "vex.h"


/// @brief elementOS
namespace eos{

    extern const controller::button*   U;
    extern const controller::button*   A;
    extern const controller::button*   B;
    extern const controller::button*   X;
    extern const controller::button*   Y;
    extern const controller::button*   U;
    extern const controller::button*   D;
    extern const controller::button*   R;
    extern const controller::button*   L;
    extern const controller::button*   R1;
    extern const controller::button*   R2;
    extern const controller::button*   L1;
    extern const controller::button*   L2;

    /// @brief 系统初始化
    /// @param p_brain 主控指针
    /// @param p_controller 遥控器指针
    void SystemInitialize(brain* p_brain , controller* p_controller);

    /// @brief elementOS主函数
    void ELEMENTOS();

    /// @brief 遥控器窗口类
    class controller_window{
    private:

    public:

        /// @brief 清屏
        static void ClearWindow();

        /// @brief 输出int, double, char*类型的数据
        /// @tparam T 数据类型
        /// @param value 数据
        /// @param c 行数
        /// @param l 列数
        template <class T>
        static void Print(T value , int c , int l);

        /// @brief 清行
        /// @param l 列数
        static void ClearLine(int l);

    };

    /// @brief 遥控器按钮类
    class controller_button{
    private:

        int                             column;//所在列数
        int                             line;//所在行数
        bool                            is_clicked;//是否按下
        int                             pressing_time;//长按时间
        const controller::button*       bind_button;//绑定的按键指针
        const char*                     text;//文字信息
        bool                            is_visual;//是否可视

        /// @brief 长按计时器
        void PressingTimer();

    public:

        controller_button();

        /// @brief 创建一个按钮
        /// @param _column 所在行数
        /// @param _line 所在列数
        /// @param _bind_button 绑定的按键指针
        /// @param _text 文字信息
        controller_button(
            int _column,
            int _line,
            const controller::button* _bind_button,
            const char* _text
        );

        /// @brief 创建一个按钮
        /// @param _bind_button 绑定的按键指针
        /// @param _text 文字信息
        controller_button(
            const controller::button* _bind_button,
            const char* _text
        );

        /// @brief 创建一个隐形按钮
        /// @param _bind_button 绑定的按键指针
        /// @param  
        controller_button(
            const controller::button* _bind_button
        );

        /// @brief 显示按钮
        /// @return 按钮指针
        controller_button* Display();

        /// @brief 显示按钮
        /// @param c 行数
        /// @param l 列数
        /// @return 按钮指针
        controller_button* Display(int c , int l);

        /// @brief 设置按钮所在列数
        /// @param c 行数
        void SetColumn(int c);

        /// @brief 设置按钮所在行数
        /// @param l 列数
        void SetLine(int l);

        /// @brief 设置按钮文字
        /// @param t 文字数组指针
        void SetText(const char* t);

        /// @brief 设置按钮绑定的遥控器按键
        /// @param btn 遥控器按键
        void BindButton(const controller::button* btn);

        /// @brief 解除按钮和遥控器按键的绑定
        void UnBindButton();

        /// @brief 获取列数
        /// @return 
        int GetColumn();

        /// @brief 获取行数
        /// @return 
        int GetLine();

        /// @brief 获取按钮绑定的遥控器按键
        /// @return 遥控器按键指针
        const controller::button* GetBindButton();

        /// @brief 判断按钮是否按下，按下返回true，否则返回false
        /// @return 
        bool IsClicked();

        /// @brief 获取长按的时间
        /// @return 
        int GetPressingTime();

    };

    /// @brief 主控窗口类
    class brain_window{

    };
    
}

#endif