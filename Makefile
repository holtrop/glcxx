.PHONY: build
build:
	./waf build

.PHONY: clean
clean:
	./waf clean

.PHONY: distclean
distclean:
	./waf distclean

.PHONY: install
install:
	./waf install

.PHONY: uninstall
uninstall:
	./waf uninstall
