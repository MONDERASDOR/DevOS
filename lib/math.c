int min(int a, int b) { return (a < b) ? a : b; }
int max(int a, int b) { return (a > b) ? a : b; }
int clamp(int x, int a, int b) { return (x < a) ? a : (x > b) ? b : x; }
int abs(int x) { return (x < 0) ? -x : x; }
