#include "servicedisks.h"

void ServiceDisks::readPhysicalDiskInfo() {
    QSettings path("HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 0\\Scsi Bus 1\\Target Id 0\\Logical Unit Id 0", QSettings::NativeFormat);
    QStringList allkeys = path.allKeys();
    QStringList valueList;

    for(int i = 0; i < allkeys.size(); i++) {
        valueList.push_back(path.value(allkeys[i]).toString());
    }

    QStringList details = valueList[2].split(QRegExp("[ ]+"));

    physicalDisk.setVendor(details[0]);
    physicalDisk.setModel(details[1] + " " + details[2]);
    physicalDisk.setSerialNumber(valueList[4]);

    //4 more parametres

    char nameBuffer[BUFFER_SIZE] = "\\\\.\\PhysicalDrive0";

    HANDLE hDrive = CreateFileA(nameBuffer,
                0,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                0,
                NULL);

    STORAGE_PROPERTY_QUERY storagePropertyQuery;
        ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
        storagePropertyQuery.PropertyId = StorageDeviceProperty;
        storagePropertyQuery.QueryType = PropertyStandardQuery;

    STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };
        DWORD dwBytesReturned = 0;
        if (!DeviceIoControl(hDrive, IOCTL_STORAGE_QUERY_PROPERTY,
            &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
            &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER),
            &dwBytesReturned, NULL))
        {
            qDebug() << "IOCTL_STORAGE_QUERY_PROPERTY - can not get the Data\n";
        }

    const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
    BYTE* pOutBuffer = new BYTE[dwOutBufferSize];
    ZeroMemory(pOutBuffer, dwOutBufferSize);

        if (!DeviceIoControl(hDrive, IOCTL_STORAGE_QUERY_PROPERTY,
            &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
            pOutBuffer, dwOutBufferSize,
            &dwBytesReturned, NULL))
        {
            qDebug() << "IOCTL_STORAGE_QUERY_PROPERTY - can not get the Data\n";
        }

    STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;
    const DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;

    char* currentStr = (char*)pOutBuffer;

    QStringList currentList = QString(currentStr + pDeviceDescriptor->ProductIdOffset).split(QRegExp("[ ]+"));

    physicalDisk.setFirmware(currentStr + pDeviceDescriptor->ProductRevisionOffset);
    physicalDisk.setMemoryInformation(currentList.at(4));
    setBusType(pDeviceDescriptor->BusType);

    CloseHandle(hDrive);
}

void ServiceDisks::readLogicalDiskInfo() {
    int number = 0;
    char diskNumberBuffer[4];
    logicalDisks.clear();

    char nameBuffer[BUFFER_SIZE];
    char fileSystemNameBuffer[BUFFER_SIZE];
    unsigned long serialNumber;

    DWORD driveDisk = GetLogicalDrives();

    for(int counter = 0; counter < BITS_AMOUNT; counter++) {
        number = ((driveDisk >> counter) & BITS_MASK);

        if(number == DISK_IS_EXISTED) {
            diskNumberBuffer[0] = char(65 + counter);
            diskNumberBuffer[1] = ':';
            diskNumberBuffer[2] = '\\';
            diskNumberBuffer[3] = 0;

            if(DRIVE_FIXED == GetDriveTypeA(diskNumberBuffer)) {
                BOOL getVolumeInformationFlag = GetVolumeInformationA(
                    diskNumberBuffer,
                    nameBuffer,
                    BUFFER_SIZE,
                    &serialNumber,
                    NULL, //&MaximumComponentLength,
                    NULL, //&FileSystemFlags,
                    fileSystemNameBuffer,
                    BUFFER_SIZE
                );

                if(getVolumeInformationFlag == false) {
                    qDebug() << "There is no memory!\n";
                    return;
                }

                ULARGE_INTEGER freeBytesAvailable;
                ULARGE_INTEGER totalNumberOfBytes;
                ULARGE_INTEGER totalNumberOfFreeBytes;

                BOOL getDiskFreeSpaceFlag = GetDiskFreeSpaceExA(
                    diskNumberBuffer,					  // directory name
                    (PULARGE_INTEGER)& freeBytesAvailable,     // bytes available to caller
                    (PULARGE_INTEGER)& totalNumberOfBytes,     // bytes on disk
                    (PULARGE_INTEGER)& totalNumberOfFreeBytes  // free bytes on disk
                );

                if (getDiskFreeSpaceFlag != 0) {
                        LogicalDisk newLogicalDisk(nameBuffer, (unsigned int)((totalNumberOfFreeBytes.QuadPart) / (1024 * 1024)),
                                                   (unsigned int)((totalNumberOfBytes.QuadPart) / (1024 * 1024) - (totalNumberOfFreeBytes.QuadPart) / (1024 * 1024)),
                                                   (unsigned int)((totalNumberOfBytes.QuadPart) / (1024 * 1024)));

                        logicalDisks.push_back(newLogicalDisk);
                } else {
                    qDebug() << "getVolumeInformationFlag == 0\n";
                }

                qDebug() << "\n";
            }
        }
    }
}

void ServiceDisks::mainWork() {
    readLogicalDiskInfo();
    readPhysicalDiskInfo();
}

QList<LogicalDisk> ServiceDisks::getLogicalDisks() {
    return logicalDisks;
}

PhysicalDisk ServiceDisks::getPhysicalDisk() {
    return physicalDisk;
}

void ServiceDisks::updateDiskData() {
    while(m_running) {
        QThread::msleep(50);

        readLogicalDiskInfo();
        readPhysicalDiskInfo();

        if(m_running) {
            emit changedDiskData();
        }
    }

    emit updateIsStoped();
}

void ServiceDisks::setRunning(bool running) {
    m_running = running;
}

void ServiceDisks::setBusType(const int busTypeNumber) {
    switch(busTypeNumber) {
        case 11: {
            physicalDisk.setInterfaceType("SATA");
        } break;
        case 1: {
            physicalDisk.setInterfaceType("UNKNOWN");
        } break;
        case 2: {
            physicalDisk.setInterfaceType("SCSI");
        } break;
        case 3: {
            physicalDisk.setInterfaceType("ATAPI");
        } break;
        default: {
            qDebug() << "Wrong parameter!\n";
        } break;
    }
}
