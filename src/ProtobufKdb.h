#ifndef __PROTOBUF_KDB_H__
#define __PROTOBUF_KDB_H__

#include <k.h>

#ifdef _WIN32
#define EXP __declspec(dllexport)
#else
#define EXP
#endif // _WIN32


extern "C"
{

  /**
   * @brief Checks that the version of the library that we linked against is
   * compatible with the version of the headers we compiled against.
   *
   * @param unused 
   * @return NULL
  */
  EXP K Init(K unused);

  /**
   * @brief Returns the libprotobuf version as an integer
   *
   * @param unused 
   * @return KI atom containing the version
  */
  EXP K Version(K unused);

  /**
   * @brief Returns the libprotobuf version as a string
   * @param unused 
   * @return Kdb char array containing the version
  */
  EXP K VersionStr(K unused);

  /**
   * @brief Converts the kdb object to a protobuf message then serializes that
   * into a char array.
   *
   * @param message_type  String containing the name of the message type.  Must
   * be the same as the message name in its .proto definition.
   * @param msg_in        Kdb object to be converted.  Its reference count will
   * be automatically decremented when control passes back to q.
   * @return              Kdb char array containing the serialized message
  */
  EXP K SerializeArray(K message_type, K msg_in);

  /**
   * @brief Identical to SerializeArray() except the intermediate protobuf
   * message is created on a google arena (helps improves memory allocation
   * performance for large messages with deep repeated/map fields).
  */
  EXP K SerializeArrayArena(K message_type, K msg_in);

  /**
   * @brief Parses the proto-serialized char array into a protobuf message then
   * converts that into the corresponding kdb object.
   *
   * @param message_type  String containing the name of the message type.  Must
   * be the same as the message name in its .proto definition.
   * @param char_array    Kdb char array containing the serialized protobuf
   * message.  Its reference count will be automatically decremented when
   * control passes back to q.
   * @return              Kdb object corresponding to the protobuf message
  */
  EXP K ParseArray(K message_type, K char_array);

  /**
   * @brief Identical to ParseArray() except the intermediate protobuf message
   * is created on a google arena (helps improves memory allocation performance
   * for large messages with deep repeated/map fields).
  */
  EXP K ParseArrayArena(K message_type, K char_array);

  /**
   * @brief Converts the kdb object to a protobuf message, serializes that then
   * writes the result to the specified file.
   *
   * @param message_type  String containing the name of the message type.  Must
   * be the same as the message name in its .proto definition.
   * @param filename      String containing the name of the file to write to.
   * @param msg_in        Kdb object to be converted.  Its reference count will
   * be automatically decremented when control passes back to q.
   * @return              NULL
  */
  EXP K SaveMessage(K message_type, K filename, K msg_in);

  /**
   * @brief Parses the proto-serialized stream from the file specified to a
   * protobuf message then converts that into the corresponding kdb object.
   *
   * @param message_type  String containing the name of the message type.  Must
   * be the same as the message name in its .proto definition.
   * @param filename      String containing the name of the file to read from.
   * @return              Kdb object corresponding to the protobuf message
  */
  EXP K LoadMessage(K message_type, K filename);

  /**
   * @brief Returns the proto schema of the specified message.
   *
   * Note: Debugging use only.  The schema is generated by the libprotobuf
   * DebugString() functionality and includes formatting/indentation for
   * display.
   *
   * @param message_type  String containing the name of the message type.  Must
   * be the same as the message name in its .proto definition.
   * @return              NULL
  */
  EXP K GetMessageSchema(K message_type);

  /**
   * @brief Adds a path to be searched when dynamically importing .proto file
   * definitions.  Can be called more than once to specify multiple import
   * locations.
   *
   * @param import_path String containing the path to be searched for proto file
   * definitions.  Can be absolute or relative.
  */
  EXP K AddProtoImportPath(K import_path);

  /**
   * @brief Dynamically imports a .proto file definition into the interface,
   * allowing the messages types defined in that file to be parsed and
   * serialised by the interface.
   *
   * @param filename  The name of the .proto file to be imported.  Must not
   * contain any directory specifiers - directory search locations should be
   * setup up beforehand using AddProtoImportPath().
   * @return          If the file fails to parse, returns an error containing
   * information on the errors and warnings which occurred.
  */
  EXP K ImportProtoFile(K filename);

  /**
   * @brief Returns a list of the message types which have been successfully
   * imported.
   *
   * Note: The list does not contain message types which have been compiled into
   * the interface.
   *
   * @return Symbol list of the successfully imported message types.
*/
  EXP K ListImportedMessageTypes(K unused);
}

#endif // __PROTOBUF_KDB_H__
