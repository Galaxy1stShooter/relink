float colormap_red(float x) {
	if (x <= 0.5) {
		return 1.07069284759359E+03 * x - 3.92901626559718E+02; // R1
	} else if (x < (4.62452380952399E+02 - 3.16199999999948E+02) / (1.05778571428574E+03 - 8.03199999999881E+02)) { // 0.57447206479
		return 1.05778571428574E+03 * x - 4.62452380952399E+02; // R2
	} else if (x < (2.16218045113087E+01 + 3.16199999999948E+02) / (8.03199999999881E+02 - 2.93462406015021E+02)) { // 0.66273668746
		return 8.03199999999881E+02 * x - 3.16199999999948E+02; // R3
	} else if (x < 0.7332708626326772) {
		return 2.93462406015021E+02 * x + 2.16218045113087E+01; // R4
	} else {
		return 0.0;
	}
}

float colormap_green(float x) {
	if (x < (2.51230508474576E+02 - 2.71026069518750E+01) / (4.27421457219241E+02 + 5.35095032144939E+02)) { // 0.23285616817
		return -5.35095032144939E+02 * x + 2.51230508474576E+02; // G1
	} else if (x < (6.91824598930488E+02 - 2.71026069518750E+01) / (4.27421457219241E+02 + 1.39121879297175E+03)) { // 0.36550493804
		return 4.27421457219241E+02 * x + 2.71026069518750E+01; // G2
	} else if (x < (6.91824598930488E+02 + 5.16725562656262E+02) / (1.02304642956372E+03 + 1.39121879297175E+03)) { // 0.500587156
		return -1.39121879297175E+03 * x + 6.91824598930488E+02; // G3
	} else if (x < 0.7332708626326772) {
		return 1.02304642956372E+03 * x - 5.16725562656262E+02; // G4
	} else {
		return 0.0;
	}
}

float colormap_blue(float x) {
	if (x < 0.3584754040051419) {
		return 1.07130443548384E+03 * x - 2.48036290322570E+02; // B1
	} else if (x < 123.0 / 251.0) {
		return 136.0;
	} else if (x < 0.7332708626326772) {
		return -1.01758796992489E+03 * x + 5.87035338345905E+02; // B2
	} else {
		return 8.98509790209691E+02 * x - 6.58851048950966E+02; // B3
	}
}

// R2 - R3 = 0
// => [x=0.5744720647924222]

// B1 - 136 = 0
// => [x=0.3584754040051419]

// B3 = 0
// => [x=0.7332708626326772]

vec4 colormap(float x) {
    float r = clamp(colormap_red(x) / 255.0, 0.0, 1.0);
    float g = clamp(colormap_green(x) / 255.0, 0.0, 1.0);
    float b = clamp(colormap_blue(x) / 255.0, 0.0, 1.0);
    return vec4(r, g, b, 1.0);
}
