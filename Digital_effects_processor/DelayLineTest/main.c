#include "delay_line.h"


int main() {
    delay_line_t *line = createDelayLine(2);
    printf("Pocetak linije: %f, Kraj linije: %f\n", startOfDelayLine(line), endOfDelayLine(line));
    shiftDelayLine(line, 1);
    printf("Pocetak linije: %f, Kraj linije: %f\n", startOfDelayLine(line), endOfDelayLine(line));
    shiftDelayLine(line, 2);
    printf("Pocetak linije: %f, Kraj linije: %f\n", startOfDelayLine(line), endOfDelayLine(line));
    shiftDelayLine(line, 3);
    printf("Pocetak linije: %f, Kraj linije: %f\n", startOfDelayLine(line), endOfDelayLine(line));
    return 0;
}