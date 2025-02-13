#include <stdint.h>
#include <stdbool.h>

const uint8_t K_A = 0x04;
const uint8_t K_B = 0x05;
const uint8_t K_C = 0x06;
const uint8_t K_D = 0x07;
const uint8_t K_E = 0x08;
const uint8_t K_F = 0x09;
const uint8_t K_G = 0x0A;
const uint8_t K_H = 0x0B;
const uint8_t K_I = 0x0C;
const uint8_t K_J = 0x0D;
const uint8_t K_K = 0x0E;
const uint8_t K_L = 0x0F;
const uint8_t K_M = 0x10;
const uint8_t K_N = 0x11;
const uint8_t K_O = 0x12;
const uint8_t K_P = 0x13;
const uint8_t K_Q = 0x14;
const uint8_t K_R = 0x15;
const uint8_t K_S = 0x16;
const uint8_t K_T = 0x17;
const uint8_t K_U = 0x18;
const uint8_t K_V = 0x19;
const uint8_t K_W = 0x1A;
const uint8_t K_X = 0x1B;
const uint8_t K_Y = 0x1C;
const uint8_t K_Z = 0x1D;
const uint8_t K_1 = 0x1E;
const uint8_t K_2 = 0x1F;
const uint8_t K_3 = 0x20;
const uint8_t K_4 = 0x21;
const uint8_t K_5 = 0x22;
const uint8_t K_6 = 0x23;
const uint8_t K_7 = 0x24;
const uint8_t K_8 = 0x25;
const uint8_t K_9 = 0x26;
const uint8_t K_0 = 0x27;

const uint8_t ENT = 0x28;  // Enter
const uint8_t ESC = 0x29;
const uint8_t BSP = 0x2A;  // Backspace
const uint8_t TAB = 0x2B;
const uint8_t SPC = 0x2C;
const uint8_t MIN = 0x2D;
const uint8_t EQL = 0x2E;
const uint8_t LPN = 0x2F; // [
const uint8_t RPN = 0x30; // ]
const uint8_t BSL = 0x31; // Back slash
const uint8_t CLN = 0x33; // ;
const uint8_t QUT = 0x34; // '
const uint8_t GRV = 0x35; // `
const uint8_t CON = 0x36; // ,
const uint8_t DOT = 0x37; // .
const uint8_t SLA = 0x38; // /
const uint8_t CPS = 0x39; // Caps lock
const uint8_t F_1 = 0x3A;
const uint8_t F_2 = 0x3B;
const uint8_t F_3 = 0x3C;
const uint8_t F_4 = 0x3D;
const uint8_t F_5 = 0x3E;
const uint8_t F_6 = 0x3F;
const uint8_t F_7 = 0x40;
const uint8_t F_8 = 0x41;
const uint8_t F_9 = 0x42;
const uint8_t F10 = 0x43;
const uint8_t F11 = 0x44;
const uint8_t F12 = 0x45;

const uint8_t CTL = 0xE0;  // left control
const uint8_t SFT = 0xE1;  // left shift
const uint8_t ALT = 0xE2;  // left alt
const uint8_t GUI = 0xE3;  // left GUI

const uint8_t HOM = 0x4A;  // Home
const uint8_t PUP = 0x4B;  // Page up
const uint8_t DEL = 0x4C;  // Delete
const uint8_t END = 0x4D;  // End
const uint8_t PDN = 0x4E;  // Page down

const uint8_t RGT = 0x4F;  // right allow
const uint8_t LFT = 0x50;  // left allow
const uint8_t DOW = 0x51;  // down allow
const uint8_t UP_ = 0x52;  // up allow

// const uint8_t = 0x;

// CUSTOM keys
const uint8_t ___ = 0x70 + 0;
const uint8_t FN_ = 0x70 + 1;
const uint8_t SYM = 0x70 + 2;
const uint8_t NUM = 0x70 + 3;
const uint8_t TLD = 0x70 + 4;  // ~
const uint8_t EXL = 0x70 + 5;  // !
const uint8_t ATM = 0x70 + 6;  // @
const uint8_t HSH = 0x70 + 7;  // #
const uint8_t DLR = 0x70 + 8;  // $
const uint8_t PER = 0x70 + 9;  // %
const uint8_t CIR = 0x70 + 10;  // ^
const uint8_t AMP = 0x70 + 11;  // &
const uint8_t AST = 0x70 + 12;  // *
const uint8_t LPR = 0x70 + 13;  // (
const uint8_t RPR = 0x70 + 14;  // )
const uint8_t UND = 0x70 + 15;  // _
const uint8_t PLU = 0x70 + 16;  // +
const uint8_t PIP = 0x70 + 17;  // |
const uint8_t LBR = 0x70 + 18;  // {
const uint8_t RBR = 0x70 + 19;  // }
const uint8_t END_OF_CUSTOM_KEY = 0x70 + 19;

// const uint8_t = 0x;


uint8_t keymap[][12*4] = {
  // DEFAULT
  {
    TAB,K_Q,K_W,K_E,K_R,K_T,K_Y,K_U,K_I,K_O,K_P,BSP,
    CTL,K_A,K_S,K_D,K_F,K_G,K_H,K_J,K_K,K_L,CLN,QUT,
    SFT,K_Z,K_X,K_C,K_V,K_B,K_N,K_M,CON,DOT,SLA,ENT,
    FN_,ALT,CTL,GUI,SYM,SPC,SPC,NUM,GUI,GUI,ALT,FN_
  },
  // SYM
  {
    //~ !   @   #   $   %   ^   &   *   (   )
    TLD,EXL,ATM,HSH,DLR,PER,CIR,AMP,AST,LPR,RPR,___,
    //                          _   +   [   ]   |
    ___,___,___,___,___,___,___,UND,PLU,LPN,RPN,PIP,
    ___,___,___,___,___,___,___,___,___,___,___,___,
    ___,___,___,___,___,___,___,___,___,___,___,___
  },
  // NUM
  {
    //` 1   2   3   4   5   6   7   8   9   0
    GRV,K_1,K_2,K_3,K_4,K_5,K_6,K_7,K_8,K_9,K_0,___,
    //                          -   =   {   }   back slash
    ___,___,___,___,___,___,___,MIN,EQL,LBR,RBR,BSL,
    ___,___,___,___,___,___,___,___,___,___,___,___,
    ___,___,___,___,___,___,___,___,___,___,___,___
  },
  // FN
  {
    // 
    ___,F_1,F_2,F_3,F_4,F_5,F_6,F_7,F_8,F_9,F10,DEL,
    ___,F11,F12,___,___,___,LFT,DOW,UP_,RGT,PUP,HOM,
    ___,___,___,___,___,___,___,___,___,___,PDN,END,
    ___,___,___,___,___,___,___,___,___,___,___,___
  },
};

bool matrix[4][12];
volatile uint8_t key_report[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

void generate_report() {
  uint8_t pushed_keys[] = {0,0,0,0,0,0,0,0};
  uint8_t num_pushed_keys = 0;

}
