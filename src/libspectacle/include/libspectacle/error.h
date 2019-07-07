#ifndef ERROR_H
#define ERROR_H
#define ERR_LOG(...) sp_err_log("[ SPECTACLE ] %s:%d in %s()\n%s\n", \
        __FILE__, __LINE__, __func__, __VA_ARGS__)
void sp_err_log(const char*, ...);
void sp_err_check(void);
void glfw_error_callback(int, const char*);
#endif /* ERROR_H */
