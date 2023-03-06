#include "commands/Align.h"
#include "commands/Drive.h"
Align::Align() {
    printf("Align initialized!");
}

void Align::Initialize() { printf("Aligning Start!!"); }


void Align::Execute() {
    printf("Alligning!");
}

void Align::End(bool interrupted) {interrupted ? printf("Not Aligned!") : printf("Aligned!");}

bool Align::IsFinished() { return false; }