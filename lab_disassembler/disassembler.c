#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 50

// Structure to represent labels
struct label {
  int out;
  int in ;
};

// Function to convert a hexadecimal character to binary
char * hexCharToBinary(char c) {
  switch (c) {
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'A': case 'a': return "1010";
    case 'B': case 'b': return "1011";
    case 'C': case 'c': return "1100";
    case 'D': case 'd': return "1101";
    case 'E': case 'e': return "1110";
    case 'F': case 'f': return "1111";
    default: printf("Invalid hexadecimal digit: %c\n", c);
    return NULL;
  }
}

// Function to convert a hexadecimal string to binary
char * hexToBinary(char * hexString) {

  int length = strlen(hexString);
  char * BinString = malloc(33 * sizeof(char));
  if (BinString == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  strcpy(BinString, "");

  for (int i = 0; i < length; i++) {
    char c = hexString[i];
    char * binary = hexCharToBinary(c);
    if (binary != NULL) {
      strcat(BinString, binary);
    } else {
      return NULL;
    }
  }
  BinString[32] = '\0';
  return BinString;
}

// Function to convert binary string to decimal
char * binaryToDecimal(const char * binaryString) {
  int length = strlen(binaryString);
  int decimal = 0;

  for (int i = length - 1, j = 0; i >= 0; i--, j++) {
    if (binaryString[i] == '1') {
      decimal += (int) pow(2, j);
    } else if (binaryString[i] != '0') {
      printf("Invalid binary digit: %c\n", binaryString[i]);
      return NULL;
    }
  }

  char * decimalString;
  decimalString = malloc(32 * sizeof(char));
  if (decimalString == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  sprintf(decimalString, "%d", decimal);

  return decimalString;
}

// Function to convert two's complement binary to decimal
char * TwosCompToDecimal(const char * binaryString) {
  int length = strlen(binaryString);
  int decimal = 0;

  for (int i = length - 1, j = 0; i >= 0; i--, j++) {
    if (binaryString[i] == '1') {
      decimal += (int) pow(2, j);
    } else if (binaryString[i] != '0') {
      printf("Invalid binary digit: %c\n", binaryString[i]);
      return NULL;
    }
  }

  if (binaryString[0] == '1') {
    decimal = decimal - pow(2, length);
  }

  char * decimalString;
  decimalString = malloc(32 * sizeof(char));
  if (decimalString == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  sprintf(decimalString, "%d", decimal);

  return decimalString;
}

// Function for R-Type instructions
void R_Type(char * BinString, char * opcode) {

  char * instruction = malloc(32 * sizeof(char));

  char * funct7 = malloc(8 * sizeof(char));
  int j = 0;
  for (int i = 0; i <= 6; i++) {
    funct7[j] = BinString[i];
    j++;
  }
  funct7[7] = '\0';

  char * rs2 = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 7; i <= 11; i++) {
    rs2[j] = BinString[i];
    j++;
  }
  rs2[5] = '\0';

  char * rs1 = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 12; i <= 16; i++) {
    rs1[j] = BinString[i];
    j++;
  }
  rs1[5] = '\0';

  char * funct3 = malloc(4 * sizeof(char));
  j = 0;
  for (int i = 17; i <= 19; i++) {
    funct3[j] = BinString[i];
    j++;
  }
  funct3[3] = '\0';

  char * rd = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 20; i <= 24; i++) {
    rd[j] = BinString[i];
    j++;
  }
  rd[5] = '\0';

  rs2 = binaryToDecimal(rs2);
  rs1 = binaryToDecimal(rs1);
  rd = binaryToDecimal(rd);

  if (strcmp(funct7, "0000000") == 0 && strcmp(funct3, "000") == 0) {
    strcpy(instruction, "add ");
  } else if (strcmp(funct7, "0100000") == 0 && strcmp(funct3, "000") == 0) {
    strcpy(instruction, "sub ");
  } else if (strcmp(funct7, "0000000") == 0 && strcmp(funct3, "100") == 0) {
    strcpy(instruction, "xor ");
  } else if (strcmp(funct7, "0000000") == 0 && strcmp(funct3, "110") == 0) {
    strcpy(instruction, "or ");
  } else if (strcmp(funct7, "0000000") == 0 && strcmp(funct3, "111") == 0) {
    strcpy(instruction, "and ");
  } else if (strcmp(funct7, "0000000") == 0 && strcmp(funct3, "001") == 0) {
    strcpy(instruction, "sll ");
  } else if (strcmp(funct7, "0000000") == 0 && strcmp(funct3, "101") == 0) {
    strcpy(instruction, "srl ");
  } else if (strcmp(funct7, "0100000") == 0 && strcmp(funct3, "101") == 0) {
    strcpy(instruction, "sra ");
  } else {
    strcpy(instruction, "");
  }

  strcat(instruction, "x");
  strcat(instruction, rd);
  strcat(instruction, ", x");
  strcat(instruction, rs1);
  strcat(instruction, ", x");
  strcat(instruction, rs2);

  puts(instruction);
}

// Function for I-Type instructions
void I_Type(char * BinString, char * opcode) {

  char * instruction = malloc(32 * sizeof(char));

  char * imm_6_11 = malloc(7 * sizeof(char));
  int j = 0;
  for (int i = 0; i <= 5; i++) {
    imm_6_11[j] = BinString[i];
    j++;
  }
  imm_6_11[6] = '\0';

  char * imm_bin = malloc(13 * sizeof(char));
  j = 0;
  for (int i = 0; i <= 11; i++) {
    imm_bin[j] = BinString[i];
    j++;
  }
  imm_bin[12] = '\0';

  char * rs1 = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 12; i <= 16; i++) {
    rs1[j] = BinString[i];
    j++;
  }
  rs1[5] = '\0';

  char * funct3 = malloc(4 * sizeof(char));
  j = 0;
  for (int i = 17; i <= 19; i++) {
    funct3[j] = BinString[i];
    j++;
  }
  funct3[3] = '\0';

  char * rd = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 20; i <= 24; i++) {
    rd[j] = BinString[i];
    j++;
  }
  rd[5] = '\0';

  rs1 = binaryToDecimal(rs1);
  rd = binaryToDecimal(rd);
  char * imm_dec = TwosCompToDecimal(imm_bin);

  if (strcmp(opcode, "0000011") == 0) {

    if (strcmp(funct3, "000") == 0) {
      strcpy(instruction, "lb x");
    } else if (strcmp(funct3, "001") == 0) {
      strcpy(instruction, "lh x");
    } else if (strcmp(funct3, "010") == 0) {
      strcpy(instruction, "lw x");
    } else if (strcmp(funct3, "011") == 0) {
      strcpy(instruction, "ld x");
    } else if (strcmp(funct3, "100") == 0) {
      strcpy(instruction, "lbu x");
    } else if (strcmp(funct3, "101") == 0) {
      strcpy(instruction, "lhu x");
    } else if (strcmp(funct3, "110") == 0) {
      strcpy(instruction, "lwu x");
    }

    strcat(instruction, rd);
    strcat(instruction, ", ");
    strcat(instruction, imm_dec);
    strcat(instruction, "(x");
    strcat(instruction, rs1);
    strcat(instruction, ")");

  } else if (strcmp(opcode, "0010011") == 0) {

    if (strcmp(funct3, "000") == 0) {
      strcpy(instruction, "addi x");
    } else if (strcmp(funct3, "100") == 0) {
      strcpy(instruction, "xori x");
    } else if (strcmp(funct3, "110") == 0) {
      strcpy(instruction, "ori x");
    } else if (strcmp(funct3, "111") == 0) {
      strcpy(instruction, "andi x");
    } else if (strcmp(funct3, "100") == 0) {
      strcpy(instruction, "xori x");
    } else if (strcmp(funct3, "001") == 0 && strcmp(imm_6_11, "000000") == 0) {
      strcpy(instruction, "slli x");
    } else if (strcmp(funct3, "101") == 0 && strcmp(imm_6_11, "000000") == 0) {
      strcpy(instruction, "srli x");
    } else if (strcmp(funct3, "101") == 0 && strcmp(imm_6_11, "010000") == 0) {
      strcpy(instruction, "srai x");
      int num;
      sscanf(imm_dec, "%d", & num);
      num = num - 1024;
      sprintf(imm_dec, "%d", num);

    }

    strcat(instruction, rd);
    strcat(instruction, ", ");
    strcat(instruction, "x");
    strcat(instruction, rs1);
    strcat(instruction, ", ");
    strcat(instruction, imm_dec);
  } else if (strcmp(opcode, "1100111") == 0) {
    strcpy(instruction, "jalr x");
    strcat(instruction, rd);
    strcat(instruction, ", ");
    strcat(instruction, "x");
    strcat(instruction, rs1);
    strcat(instruction, ", ");
    strcat(instruction, imm_dec);
  }

  puts(instruction);
}

// Function for S-Type instructions
void S_Type(char * BinString, char * opcode) {

  char * instruction = malloc(32 * sizeof(char));

  char * imm_11_5 = malloc(8 * sizeof(char));
  int j = 0;
  for (int i = 0; i <= 6; i++) {
    imm_11_5[j] = BinString[i];
    j++;
  }
  imm_11_5[7] = '\0';

  char * rs2 = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 7; i <= 11; i++) {
    rs2[j] = BinString[i];
    j++;
  }
  rs2[5] = '\0';

  char * rs1 = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 12; i <= 16; i++) {
    rs1[j] = BinString[i];
    j++;
  }
  rs1[5] = '\0';

  char * funct3 = malloc(4 * sizeof(char));
  j = 0;
  for (int i = 17; i <= 19; i++) {
    funct3[j] = BinString[i];
    j++;
  }
  funct3[3] = '\0';

  char * imm_4_0 = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 20; i <= 24; i++) {
    imm_4_0[j] = BinString[i];
    j++;
  }
  imm_4_0[5] = '\0';

  if (strcmp(funct3, "000") == 0) {
    strcpy(instruction, "sb x");
  } else if (strcmp(funct3, "001") == 0) {
    strcpy(instruction, "sh x");
  } else if (strcmp(funct3, "010") == 0) {
    strcpy(instruction, "sw x");
  } else if (strcmp(funct3, "011") == 0) {
    strcpy(instruction, "sd x");
  }

  char * imm_bin = malloc(13 * sizeof(char));
  strcpy(imm_bin, imm_11_5);
  strcat(imm_bin, imm_4_0);
  char * imm_dec = TwosCompToDecimal(imm_bin);

  rs2 = binaryToDecimal(rs2);
  rs1 = binaryToDecimal(rs1);

  strcat(instruction, rs2);
  strcat(instruction, ", ");
  strcat(instruction, imm_dec);
  strcat(instruction, "(x");
  strcat(instruction, rs1);
  strcat(instruction, ")");
  puts(instruction);
}

// Function for B-Type instructions
void B_Type(char * BinString, char * opcode) {

  char * instruction = malloc(32 * sizeof(char));

  char * imm_12 = malloc(2 * sizeof(char));
  imm_12[0] = BinString[0];
  imm_12[1] = '\0';

  char * imm_10_5 = malloc(7 * sizeof(char));
  int j = 0;
  for (int i = 1; i <= 6; i++) {
    imm_10_5[j] = BinString[i];
    j++;
  }
  imm_10_5[6] = '\0';

  char * rs2 = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 7; i <= 11; i++) {
    rs2[j] = BinString[i];
    j++;
  }
  rs2[5] = '\0';

  char * rs1 = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 12; i <= 16; i++) {
    rs1[j] = BinString[i];
    j++;
  }
  rs1[5] = '\0';

  char * funct3 = malloc(4 * sizeof(char));
  j = 0;
  for (int i = 17; i <= 19; i++) {
    funct3[j] = BinString[i];
    j++;
  }
  funct3[3] = '\0';

  char * imm_4_1 = malloc(5 * sizeof(char));
  j = 0;
  for (int i = 20; i <= 23; i++) {
    imm_4_1[j] = BinString[i];
    j++;
  }
  imm_4_1[4] = '\0';

  char * imm_11 = malloc(2 * sizeof(char));
  imm_11[0] = BinString[24];
  imm_11[1] = '\0';

  char * imm_bin = malloc(14 * sizeof(char));
  strcpy(imm_bin, imm_12);
  strcat(imm_bin, imm_11);
  strcat(imm_bin, imm_10_5);
  strcat(imm_bin, imm_4_1);
  strcat(imm_bin, "0");

  rs1 = binaryToDecimal(rs1);
  rs2 = binaryToDecimal(rs2);
  char * imm_dec = TwosCompToDecimal(imm_bin);

  if (strcmp(funct3, "000") == 0) {
    strcpy(instruction, "beq x");
  } else if (strcmp(funct3, "001") == 0) {
    strcpy(instruction, "bne x");
  } else if (strcmp(funct3, "100") == 0) {
    strcpy(instruction, "blt x");
  } else if (strcmp(funct3, "101") == 0) {
    strcpy(instruction, "bge x");
  } else if (strcmp(funct3, "110") == 0) {
    strcpy(instruction, "bltu x");
  } else if (strcmp(funct3, "111") == 0) {
    strcpy(instruction, "bgeu x");
  }

  strcat(instruction, rs1);
  strcat(instruction, ", x");
  strcat(instruction, rs2);
  strcat(instruction, ", ");

  printf("%s", instruction);
}

// Function for U-Type instructions
void U_Type(char * BinString, char * opcode) {

  char * instruction = malloc(32 * sizeof(char));

  char * imm_31_12 = malloc(21 * sizeof(char));
  int j = 0;
  for (int i = 0; i <= 19; i++) {
    imm_31_12[j] = BinString[i];
    j++;
  }
  imm_31_12[20] = '\0';

  char * rd = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 20; i <= 24; i++) {
    rd[j] = BinString[i];
    j++;
  }
  rd[5] = '\0';

  rd = binaryToDecimal(rd);
  int imm_dec = strtol(imm_31_12, NULL, 2);

  char * imm_hex = malloc(6 * sizeof(char));
  sprintf(imm_hex, "%X", imm_dec);

  strcpy(instruction, "lui x");
  strcat(instruction, rd);
  strcat(instruction, ", 0x");
  strcat(instruction, imm_hex);

  puts(instruction);
}

// Function for J-Type instructions
void J_Type(char * BinString, char * opcode) {

  char * instruction = malloc(32 * sizeof(char));

  char * imm_20 = malloc(2 * sizeof(char));
  imm_20[0] = BinString[0];
  imm_20[1] = '\0';

  char * imm_10_1 = malloc(11 * sizeof(char));
  int j = 0;
  for (int i = 1; i <= 10; i++) {
    imm_10_1[j] = BinString[i];
    j++;
  }
  imm_10_1[10] = '\0';

  char * imm_11 = malloc(2 * sizeof(char));
  imm_11[0] = BinString[11];
  imm_11[1] = '\0';

  char * imm_19_12 = malloc(9 * sizeof(char));
  j = 0;
  for (int i = 12; i <= 19; i++) {
    imm_19_12[j] = BinString[i];
    j++;
  }
  imm_19_12[8] = '\0';

  char * imm_bin = malloc(22 * sizeof(char));
  strcpy(imm_bin, imm_20);
  strcat(imm_bin, imm_19_12);
  strcat(imm_bin, imm_11);
  strcat(imm_bin, imm_10_1);
  strcat(imm_bin, "0");

  char * imm_dec = TwosCompToDecimal(imm_bin);

  char * rd = malloc(6 * sizeof(char));
  j = 0;
  for (int i = 20; i <= 24; i++) {
    rd[j] = BinString[i];
    j++;
  }
  rd[5] = '\0';

  rd = binaryToDecimal(rd);

  strcpy(instruction, "jal x");
  strcat(instruction, rd);
  strcat(instruction, ", ");

  printf("%s", instruction);
}

// Function to return line number for branches and jumps
int Return_LineNo(char * BinString, char * opcode) {

  if (strcmp(opcode, "1100011") == 0) {
    char * imm_12 = malloc(2 * sizeof(char));
    imm_12[0] = BinString[0];
    imm_12[1] = '\0';

    char * imm_10_5 = malloc(7 * sizeof(char));
    int j = 0;
    for (int i = 1; i <= 6; i++) {
      imm_10_5[j] = BinString[i];
      j++;
    }
    imm_10_5[6] = '\0';

    char * imm_4_1 = malloc(5 * sizeof(char));
    j = 0;
    for (int i = 20; i <= 23; i++) {
      imm_4_1[j] = BinString[i];
      j++;
    }
    imm_4_1[4] = '\0';

    char * imm_11 = malloc(2 * sizeof(char));
    imm_11[0] = BinString[24];
    imm_11[1] = '\0';

    char * imm_bin = malloc(14 * sizeof(char));
    strcpy(imm_bin, imm_12);
    strcat(imm_bin, imm_11);
    strcat(imm_bin, imm_10_5);
    strcat(imm_bin, imm_4_1);
    strcat(imm_bin, "0");

    char * imm_dec = TwosCompToDecimal(imm_bin);
    int decimal = 0;
    sscanf(imm_dec, "%d", & decimal);
    return decimal / 4;
  } else if (strcmp(opcode, "1101111") == 0) {
    char * imm_20 = malloc(2 * sizeof(char));
    imm_20[0] = BinString[0];
    imm_20[1] = '\0';

    char * imm_10_1 = malloc(11 * sizeof(char));
    int j = 0;
    for (int i = 1; i <= 10; i++) {
      imm_10_1[j] = BinString[i];
      j++;
    }
    imm_10_1[10] = '\0';

    char * imm_11 = malloc(2 * sizeof(char));
    imm_11[0] = BinString[11];
    imm_11[1] = '\0';

    char * imm_19_12 = malloc(9 * sizeof(char));
    j = 0;
    for (int i = 12; i <= 19; i++) {
      imm_19_12[j] = BinString[i];
      j++;
    }
    imm_19_12[8] = '\0';

    char * imm_bin = malloc(22 * sizeof(char));
    strcpy(imm_bin, imm_20);
    strcat(imm_bin, imm_19_12);
    strcat(imm_bin, imm_11);
    strcat(imm_bin, imm_10_1);
    strcat(imm_bin, "0");

    char * imm_dec = TwosCompToDecimal(imm_bin);
    int decimal = 0;
    sscanf(imm_dec, "%d", & decimal);
    return decimal / 4;
  }
}

int main() {

  char * instructions[MAX];
  for (int i = 0; i < MAX; i++) {
    instructions[i] = malloc(20 * sizeof(char));
  }

// Open the input file for reading
  FILE * file;
  char hexString[20];

  file = fopen("input1.txt", "r");

  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  int j;
  for (j = 0; fgets(hexString, 20, file) != NULL; j++) {
    hexString[8] = '\0';
    strcpy(instructions[j], hexString);
  }

// Close the file
  fclose(file);

  int Total_instructions = j;

// Free memory allocated for instructions
  while (j <= MAX-1) {
    free(instructions[j]);
    instructions[j] = NULL;
    j++;
  }

  struct label * label[Total_instructions];
  for (int i = 0; i < Total_instructions; i++) {
    label[i] = malloc(sizeof(struct label));
    (label[i]) -> out = 0;
    (label[i]) -> in = 0;
  }

  int Total_labels = 1;
  for (int i = 0; instructions[i] != NULL; i++) {
    char * BinString;
    char opcode[8];
    int j = 0;

    BinString = hexToBinary(instructions[i]);

    j = 0;
    for (int i = 25; i <= 31; i++) {
      opcode[j] = BinString[i];
      j++;
    }
    opcode[7] = '\0';

    if (strcmp(opcode, "1100011") == 0 || strcmp(opcode, "1101111") == 0) {
      j = i + Return_LineNo(BinString, opcode);
      if (label[j] -> out == 0) {
        label[j] -> out = Total_labels;
        Total_labels++;
      }
      label[i] -> in = label[j] -> out;
    }
  }

  printf("\n");
  for (int i = 0; instructions[i] != NULL; i++) {

    if (label[i] -> out != 0) {
      printf("\nL%d: ", label[i] -> out);
    }

    char * BinString;
    char opcode[8];

    BinString = hexToBinary(instructions[i]);

    j = 0;
    for (int i = 25; i <= 31; i++) {
      opcode[j] = BinString[i];
      j++;
    }
    opcode[7] = '\0';

    if (strcmp(opcode, "0110011") == 0) {
      R_Type(BinString, opcode);
    } else if (strcmp(opcode, "0000011") == 0 || strcmp(opcode, "0010011") == 0 || strcmp(opcode, "1100111") == 0) {
      I_Type(BinString, opcode);
    } else if (strcmp(opcode, "0100011") == 0) {
      S_Type(BinString, opcode);
    } else if (strcmp(opcode, "1100011") == 0) {
      B_Type(BinString, opcode);
      if (label[i] -> in != 0) {
        printf("L%d\n", label[i] -> in);
      }
    } else if (strcmp(opcode, "0110111") == 0) {
      U_Type(BinString, opcode);
    } else if (strcmp(opcode, "1101111") == 0) {
      J_Type(BinString, opcode);
      if (label[i] -> in != 0) {
        printf("L%d\n", label[i] -> in);
      }
    }
  }
  printf("\n");
}