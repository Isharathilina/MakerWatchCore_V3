#define DEFAULT_G_MOTOR_ADDRESS 0x32


/* define the number of channels supported by the driver */
enum MTDRV_motor_channel{
  MTDRV_CHANNEL_01,
  MTDRV_CHANNEL_02,
  MTDRV_motor_channel_cnt 
};

/* define the number of status supported by the driver */
enum MTDRV_channel_status{
  MTDRV_STATUS_FOWARD,
  MTDRV_STATUS_BACKWARD,
  MTDRV_STATUS_BREAK,
  MTDRV_STATUS_RELEASE,
  MTDRV_channel_status_cnt
};

enum G_MOTOR_DIRECTION_t{
  GMOTOR_FOWARD,
  GMOTOR_BACKWARD,
};

/********************************************
defines the set of basic commands accepted by device
*/
enum driver_cmd_t{
  DRIVER_CMD_ENABLE_MOTOR,
  DRIVER_CMD_DISABLE_MOTOR,
  DRIVER_CMD_SET_DIRECTION,
  DRIVER_CMD_SET_SPEED,
  DRIVER_CMD_BREAK_MOTOR,
  DRIVER_CMD_SET_RELEAS_MOTOR,
  
  DRIVER_CMD_GET_STATUS,  
  driver_cmd_basic_cnt
};

struct G_MOTOR_STATUS{
  bool isEnable ;
  MTDRV_channel_status status;
  uint8_t speed;
};


class G_MOTOR{
  private:
  int i2c_address;

  public:
  G_MOTOR();
  G_MOTOR(int address);
  int init(int address);
  int setDirection(MTDRV_motor_channel channel, G_MOTOR_DIRECTION_t direction);
  int breake(MTDRV_motor_channel channel);
  int releas(MTDRV_motor_channel channel);
  int setSpeed(MTDRV_motor_channel channel, int speed);
  int enableChannel(MTDRV_motor_channel channel);
  int disableChannel(MTDRV_motor_channel channel);
  struct G_MOTOR_STATUS* getStatus(MTDRV_motor_channel channel);
};
