#ifndef IDISPLAY_H_
#define IDISPLAY_H_

class IDisplayNC {
    public:
        virtual void showError(string title, string text) = 0;
        virtual void showError(string text) = 0;

        virtual void showWarning(string title, string text) = 0;
        virtual void showWarning(string text) = 0;

        virtual void showNotification(string title, string text) = 0;
        virtual void showNotification(string text) = 0;
};

#endif