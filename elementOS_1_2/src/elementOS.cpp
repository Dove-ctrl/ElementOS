#include "elementOS.h"

namespace eos{

    brain*              _brain;//主控指针
    controller*         _controller;//遥控器指针

    const controller::button*   A   =   &(_controller->ButtonA);
    const controller::button*   B   =   &(_controller->ButtonB);
    const controller::button*   X   =   &(_controller->ButtonX);
    const controller::button*   Y   =   &(_controller->ButtonY);
    const controller::button*   U   =   &(_controller->ButtonUp);
    const controller::button*   D   =   &(_controller->ButtonDown);
    const controller::button*   R   =   &(_controller->ButtonRight);
    const controller::button*   L   =   &(_controller->ButtonLeft);
    const controller::button*   R1   =   &(_controller->ButtonR1);
    const controller::button*   R2   =   &(_controller->ButtonR2);
    const controller::button*   L1   =   &(_controller->ButtonL1);
    const controller::button*   L2   =   &(_controller->ButtonL2);
    
    void SystemInitialize(brain* p_brain , controller* p_controller){
        _brain = p_brain; _controller = p_controller;
        _controller->Screen.clearScreen();
        _brain->Screen.clearScreen();
    }

//////////////////////controller_window/////////////////////////////////////////////////////////

    void controller_window::ClearLine(int l){
        _controller->Screen.clearLine(l);
    }

    void controller_window::ClearWindow(){
        _controller->Screen.clearScreen();
    }

    template<class T>
    void controller_window::Print(T value , int c , int l){
        _controller->Screen.clearLine(l);
        _controller->Screen.setCursor(c , l);
        _controller->Screen.print(value);
    }
    template void controller_window::Print(int value , int c , int l);
    template void controller_window::Print(double value , int c , int l);
    template void controller_window::Print(const char* value , int c , int l);

/////////////////////controller_button/////////////////////////////////////////////

    void controller_button::PressingTimer(){
        while (true)
        {
            if(bind_button->pressing()){
                pressing_time += 5;
            }else{
                pressing_time = 0;
            }
            wait(5,msec);
        }
    }

    controller_button::controller_button(){
        bind_button = NULL;
        text = NULL;
        //vex::thread btn_prs_t(void(*PressingTimer));
    }

    controller_button::controller_button(
        const controller::button* _bind_button,
        const char* _text
    ){
        bind_button = _bind_button;
        text = _text;
        is_visual = true;
        //vex::thread btn_prs_t(void(*PressingTimer));
    }

    controller_button::controller_button(
        int _column,
        int _line,
        const controller::button* _bind_button,
        const char* _text
    ){
        column = _column;
        line = _line;
        bind_button = _bind_button;
        text = _text;
        is_visual = true;
        //vex::thread btn_prs_t(void(*PressingTimer));
    }

    controller_button::controller_button(
        const controller::button* _bind_button
    ){
        bind_button = _bind_button;
        is_visual = false;
        //vex::thread btn_prs_t(void(*PressingTimer));
    }

    controller_button* controller_button::Display(){
        if(is_visual){
            _controller->Screen.setCursor(column , line);
            _controller->Screen.print(text);
            return this;
        }else{
            return NULL;
        }
    }

    controller_button* controller_button::Display(int c , int l){
        if(is_visual){
            column = c; line = l;
            _controller->Screen.setCursor(column , line);
            _controller->Screen.print(text);
            return this;
        }else{
            return NULL;
        }
    }

    void controller_button::SetColumn(int c){
        column = c;
    }

    void controller_button::SetLine(int l){
        line = l;
    }

    void controller_button::SetText(const char* t){
        text = t;
    }

    void controller_button::BindButton(const controller::button* btn){
        bind_button = btn;
    }

    void controller_button::UnBindButton(){
        bind_button = NULL;
    }

    int controller_button::GetColumn(){
        return column;
    }

    int controller_button::GetLine(){
        return line;
    }

    const controller::button* controller_button::GetBindButton(){
        return bind_button;
    }

    bool controller_button::IsClicked(){
        is_clicked = bind_button->pressing();
        return is_clicked;
    }

    int controller_button::GetPressingTime(){
        return pressing_time;
    }
}