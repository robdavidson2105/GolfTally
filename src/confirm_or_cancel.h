typedef void (*confirm_or_cancel_callback)(bool);

void show_confirm_or_cancel(confirm_or_cancel_callback ptr_confirm_cancel_callback);
void hide_confirm_or_cancel(void);
