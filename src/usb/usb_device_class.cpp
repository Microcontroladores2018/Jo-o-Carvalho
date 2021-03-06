#include <usb/usb_device_class.h>




USB_DEVICE_CLASS::USB_DEVICE_CLASS(uint8_t interfaces, uint8_t inendpoints, uint8_t outendpoints, std::initializer_list<const char*> stringlist, uint8_t enabled):
	_stringlist(stringlist)
{
	if(enabled){
		while(interfaces--)
			_interfaces.push_back(_numinterfaces++);
		while(inendpoints--)
			_inendpoints.push_back(0x80 | _numinendpoints++);
		while(outendpoints--)
			_outendpoints.push_back(_numoutendpoints++);
		_firstdescriptorstring=_numdescriptorstrings;
		_numdescriptorstrings+=_stringlist.size();
		_usb_device_classes_list.push_back(this);
	}
}


uint8_t* USB_DEVICE_CLASS::GetDescriptorString(uint8_t index) {
	int8_t ind = index - _firstdescriptorstring;
	if (ind >= 0 && ind < (int8_t) (_stringlist.size())) {
		return (uint8_t*) (_stringlist[ind]);
	}
	return 0;
}
