/**
 * @file task_manager.h
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief RTOS görevlerinin ve iş mantığının yönetildiği ana katman dosyası.
 * @version 0.2
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef INC_APP_TASK_MANAGER_H_
#define INC_APP_TASK_MANAGER_H_

/**
 * @brief RTOS görevlerinin ayrıştırılmış ana döngü fonksiyonları.
 */
void TaskManager_Dispatch_Process(void);
void TaskManager_DriveRight_Process(void);
void TaskManager_DriveLeft_Process(void);
void TaskManager_DriveRamp_Process(void);

#endif /* INC_APP_TASK_MANAGER_H_ */