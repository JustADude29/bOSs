export PROJECTDIR = $(CURDIR)
export SCRIPTSDIR = $(PROJECTDIR)/scripts

help:
	@echo "Make <action>:"
	@echo " clean"
	@echo " build"
	@echo " run"

clean:
	$(MAKE) headerlog header="Cleaning"
	bash -c "$(SCRIPTSDIR)/clean.sh"
	@echo
	@echo

build: 
	$(MAKE) headerlog header="Building"
	bash -c "$(SCRIPTSDIR)/iso.sh"
	@echo
	@echo

iso: 
	$(MAKE) headerlog header="Building ISO"
	bash -c "$(SCRIPTSDIR)/iso.sh"

run: 
	$(MAKE) headerlog header="Running"
	bash -c "$(SCRIPTSDIR)/qemu.sh"
	@echo
	@echo

headerlog:
	@echo
	@echo
	@echo "==== $(header)":
	@echo
	@echo

.PHONY: help build clean

