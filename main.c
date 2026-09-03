/* USER CODE BEGIN Includes */
#include "car_driver.h"
/* USER CODE END Includes */

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE BEGIN 3 */
    /*==================== 【模块5：主循环业务逻辑模块】 ====================*/
    float dist = get_hcsr04_distance();
    uint8_t black_flag = read_black_line();

    //逻辑1：检测到黑线，优先处理，禁止压黑线
    if(black_flag != 0)
    {
        car_stop();
        HAL_Delay(200);
        car_backward();
        HAL_Delay(300);
        car_stop();
        HAL_Delay(200);

        if(black_flag == 1)
        {
            car_right();
            HAL_Delay(400);
        }
        else if(black_flag == 2)
        {
            car_left();
            HAL_Delay(400);
        }
        else if(black_flag == 3)
        {
            car_right();
            HAL_Delay(600);
        }
        car_stop();
    }
    //逻辑2：无黑线，检测前方障碍物避障
    else if(dist < OBSTACLE_DIST)
    {
        car_stop();
        HAL_Delay(200);
        car_backward();
        HAL_Delay(300);
        car_stop();
        HAL_Delay(200);
        car_left();
        HAL_Delay(500);
        car_stop();
    }
    //逻辑3：无黑线无障碍物，正常前进
    else
    {
        car_forward();
    }
    /*========================================================================*/
    /* USER CODE END 3 */
  }
  /* USER CODE END WHILE */
}

