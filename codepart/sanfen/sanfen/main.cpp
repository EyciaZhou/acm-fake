double l = -ma, r = ma, m, mm;
for (int t = 0; t < 100; t++) {
	m = (l + r) / 2;
	mm = (m + r) / 2;
	if (val(m) < val(mm)) {
		r = mm;
	} else {
		l = m;
	}
}
printf("%.10lf\n", val(l));