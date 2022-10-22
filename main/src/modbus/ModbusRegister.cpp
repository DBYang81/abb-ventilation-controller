#include "ModbusRegister.h"

ModbusRegister::ModbusRegister(ModbusMaster *master, int address, bool holdingRegister)
	:m(master), addr(address), hr(holdingRegister) {
	// TODO Auto-generated constructor stub

}

ModbusRegister::~ModbusRegister() {
	// TODO Auto-generated destructor stub
}

int ModbusRegister::read() {
	uint8_t result = hr ? m->readHoldingRegisters(addr, 1) : m->readInputRegisters(addr, 1) ;
	// check if we were able to read
	if (result == m->ku8MBSuccess) {
		return m->getResponseBuffer(0);
	}
	return -1;
}

uint8_t ModbusRegister::write(int value)
{
	// write only if not
	if(hr) return m->writeSingleRegister(addr, value); // not checking if write succeeds
	return 0xE2;
}
