#include <frc2/command/SubsystemBase.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/SpanExtras.h"
#include <span>
#include <spanstream>


class Vision : public frc2::SubsystemBase {
 public:
  Vision();

  double GetTargetX();
  void SelectPipeline(int id);

 private:
  std::shared_ptr<nt::NetworkTable> m_networkTable;
};