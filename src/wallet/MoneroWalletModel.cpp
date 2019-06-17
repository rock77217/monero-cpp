#include "MoneroWallet.h"

#include "utils/MoneroUtils.h"
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cryptonote; // TODO: delete?
using namespace epee; // TODO: delete?

/**
 * Public library interface.
 */
namespace monero {

  // ----------------------- UNDECLARED PRIVATE HELPERS -----------------------


  // -------------------------- MODEL SERIALIZATION ---------------------------

  boost::property_tree::ptree MoneroAccount::toPropertyTree() const {
    //cout << "MoneroAccount::toPropertyTree(node)" << endl;
    boost::property_tree::ptree node;
    if (index != boost::none) node.put("index", *index);
    if (primaryAddress != boost::none) node.put("primaryAddress", *primaryAddress);
    if (balance != boost::none) node.put("balance", *balance);
    if (unlockedBalance != boost::none) node.put("unlockedBalance", *unlockedBalance);
    if (!subaddresses.empty()) node.add_child("subaddresses", MoneroUtils::toPropertyTree(subaddresses));
//    if (!subaddresses.empty()) {
//      boost::property_tree::ptree subaddressesNode;
//      for (const MoneroSubaddress& subaddress : subaddresses) {
//        subaddressesNode.push_back(std::make_pair("", subaddress.toPropertyTree()));
//      }
//      node.add_child("subaddresses", subaddressesNode);
//    }
    return node;
  }

  boost::property_tree::ptree MoneroSubaddress::toPropertyTree() const {
    //cout << "MoneroSubaddress::toPropertyTree(node)" << endl;
    boost::property_tree::ptree node;
    if (accountIndex != boost::none) node.put("accountIndex", *accountIndex);
    if (index != boost::none) node.put("index", *index);
    if (address != boost::none) node.put("address", *address);
    if (label != boost::none) node.put("label", *label);
    if (balance != boost::none) node.put("balance", *balance);
    if (unlockedBalance != boost::none) node.put("unlockedBalance", *unlockedBalance);
    if (numUnspentOutputs != boost::none) node.put("numUnspentOutputs", *numUnspentOutputs);
    if (isUsed != boost::none) node.put("isUsed", *isUsed);
    if (numBlocksToUnlock != boost::none) node.put("numBlocksToUnlock", *numBlocksToUnlock);
    return node;
  }

  boost::property_tree::ptree MoneroTxWallet::toPropertyTree() const {
    //cout << "MoneroTxWallet::toPropertyTree(node)" << endl;
    boost::property_tree::ptree node = MoneroTx::toPropertyTree();
    if (!vouts.empty()) throw runtime_error("vouts not implemented");
    if (!incomingTransfers.empty()) node.add_child("incomingTransfers", MoneroUtils::toPropertyTree(incomingTransfers));
    if (outgoingTransfer != boost::none) throw runtime_error("outgoingTransfers not implemented");
    if (note != boost::none) node.put("note", *note);
    return node;
  }

  boost::property_tree::ptree MoneroTxRequest::toPropertyTree() const {
    //cout << "MoneroTxRequest::toPropertyTree(node)" << endl;
    throw runtime_error("Not implemented");
  }

  boost::property_tree::ptree MoneroTransfer::toPropertyTree() const {
    //cout << "MoneroTransfer::toPropertyTree(node)" << endl;
    boost::property_tree::ptree node;
    if (amount != boost::none) node.put("amount", *amount);
    if (accountIndex != boost::none) node.put("accountIndex", *accountIndex);
    if (numSuggestedConfirmations != boost::none) node.put("numSuggestedConfirmations", *numSuggestedConfirmations);
    return node;
  }

  boost::property_tree::ptree MoneroIncomingTransfer::toPropertyTree() const {
    //cout << "MoneroIncomingTransfer::toPropertyTree(node)" << endl;
    boost::property_tree::ptree node = MoneroTransfer::toPropertyTree();
    if (subaddressIndex != boost::none) node.put("subaddressIndex", *subaddressIndex);
    if (address != boost::none) node.put("address", *address);
    return node;
  }

  boost::property_tree::ptree MoneroOutgoingTransfer::toPropertyTree() const {
    //cout << "MoneroOutgoingTransfer::toPropertyTree(node)" << endl;
    boost::property_tree::ptree node = MoneroTransfer::toPropertyTree();
    if (!subaddressIndices.empty()) throw runtime_error("subaddressIndices not implemented");
    if (!addresses.empty()) throw runtime_error("addresses not implemented");
    if (!destinations.empty()) throw runtime_error("destinations not implemented");
    return node;
  }

  //boost::property_tree::ptree MoneroUtils::txWalletToPropertyTree(const MoneroTxWallet& tx) {
  //  cout << "txWalletToPropertyTree(tx)" << endl;
  //  boost::property_tree::ptree txNode = txToPropertyTree(tx);
  //  if (!tx.vouts.empty()) throw runtime_error("not implemented");
  //  if (!tx.incomingTransfers.empty()) throw runtime_error("not implemented");
  //  if (tx.outgoingTransfer != boost::none) throw runtime_error("not implemented");
  //  if (tx.numSuggestedConfirmations != boost::none) txNode.put("numSuggestedConfirmations", *tx.numSuggestedConfirmations);
  //  if (tx.note != boost::none) txNode.put("note", *tx.note);
  //  return txNode;
  //}
  //
  //boost::property_tree::ptree MoneroUtils::txRequestToPropertyTree(const MoneroTxRequest& tx) {
  //  cout << "txWalletToPropertyTree(tx)" << endl;
  //  boost::property_tree::ptree txNode = txWalletToPropertyTree(tx);
  //  if (tx.isOutgoing != boost::none) txNode.put("isOutgoing", *tx.isOutgoing);
  //  if (tx.isIncoming != boost::none) txNode.put("isIncoming", *tx.isIncoming);
  //  if (!tx.txIds.empty()) throw runtime_error("not implemented");
  //  if (tx.hasPaymentId != boost::none) txNode.put("hasPaymentId", *tx.hasPaymentId);
  //  if (!tx.paymentIds.empty()) throw runtime_error("not implemented");
  //  if (tx.minHeight != boost::none) txNode.put("minHeight", *tx.minHeight);
  //  if (tx.maxHeight != boost::none) txNode.put("maxHeight", *tx.maxHeight);
  //  if (tx.includeOutputs != boost::none) txNode.put("includeOutputs", *tx.includeOutputs);
  //  if (tx.transferRequest != boost::none) throw runtime_error("not implemented");
  //  return txNode;
  //}

  // --------------------------------- REQUESTS -------------------------------

  bool MoneroTransferRequest::meetsCriteria(const MoneroTransfer& transfer) const {

    throw runtime_error("Not implemented");


//    if (transfer == null) return false;
//
//    // filter on common fields
//    if (this.getIsIncoming() != null && this.getIsIncoming() != transfer.getIsIncoming()) return false;
//    if (this.getIsOutgoing() != null && this.getIsOutgoing() != transfer.getIsOutgoing()) return false;
//    if (this.getAmount() != null && this.getAmount().compareTo(transfer.getAmount()) != 0) return false;
//    if (this.getAccountIndex() != null && !this.getAccountIndex().equals(transfer.getAccountIndex())) return false;
//
//    // filter on incoming fields
//    if (transfer instanceof MoneroIncomingTransfer) {
//      if (Boolean.TRUE.equals(this.getHasDestinations())) return false;
//      MoneroIncomingTransfer inTransfer = (MoneroIncomingTransfer) transfer;
//      if (this.getAddress() != null && !this.getAddress().equals(inTransfer.getAddress())) return false;
//      if (this.getAddresses() != null && !this.getAddresses().contains(inTransfer.getAddress())) return false;
//      if (this.getSubaddressIndex() != null && !this.getSubaddressIndex().equals(inTransfer.getSubaddressIndex())) return false;
//      if (this.getSubaddressIndices() != null && !this.getSubaddressIndices().contains(inTransfer.getSubaddressIndex())) return false;
//    }
//
//    // filter on outgoing fields
//    else if (transfer instanceof MoneroOutgoingTransfer) {
//      MoneroOutgoingTransfer outTransfer = (MoneroOutgoingTransfer) transfer;
//
//      // filter on addresses
//      if (this.getAddress() != null && (outTransfer.getAddresses() == null || !outTransfer.getAddresses().contains(this.getAddress()))) return false;   // TODO: will filter all transfers if they don't contain addresses
//      if (this.getAddresses() != null) {
//        List<String> intersections = new ArrayList<String>(this.getAddresses());
//        intersections.retainAll(outTransfer.getAddresses());
//        if (intersections.isEmpty()) return false;  // must have overlapping addresses
//      }
//
//      // filter on subaddress indices
//      if (this.getSubaddressIndex() != null && (outTransfer.getSubaddressIndices() == null || !outTransfer.getSubaddressIndices().contains(this.getSubaddressIndex()))) return false;
//      if (this.getSubaddressIndices() != null) {
//        List<Integer> intersections = new ArrayList<Integer>(this.getSubaddressIndices());
//        intersections.retainAll(outTransfer.getSubaddressIndices());
//        if (intersections.isEmpty()) return false;  // must have overlapping subaddress indices
//      }
//
//      // filter on having destinations
//      if (this.getHasDestinations() != null) {
//        if (this.getHasDestinations() && outTransfer.getDestinations() == null) return false;
//        if (!this.getHasDestinations() && outTransfer.getDestinations() != null) return false;
//      }
//
//      // filter on destinations TODO: start with test for this
////    if (this.getDestionations() != null && this.getDestionations() != transfer.getDestionations()) return false;
//    }
//
//    // otherwise invalid type
//    else throw new RuntimeException("Transfer must be MoneroIncomingTransfer or MoneroOutgoingTransfer");
//
//    // filter with tx filter
//    if (this.getTxRequest() != null && !this.getTxRequest().meetsCriteria(transfer.getTx())) return false;
//    return true;
  }
}
